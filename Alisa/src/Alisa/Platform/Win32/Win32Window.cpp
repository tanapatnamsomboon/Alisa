#include "pch.h"
#include "Win32Window.h"

#include "Alisa/Events/ApplicationEvent.h"
#include "Alisa/Events/KeyEvent.h"

namespace Alisa
{
    LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        if (uMsg == WM_NCCREATE)
        {
            const auto create = reinterpret_cast<LPCREATESTRUCT>(lParam);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(create->lpCreateParams));
        }

        if (const auto* window = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA)))
        {
            switch (uMsg)
            {
            case WM_CLOSE:
                if (window->m_Data.EventCallback)
                {
                    WindowCloseEvent event;
                    window->m_Data.EventCallback(event);
                }
                return 0;
            case WM_SIZE:
                if (window->m_Data.EventCallback)
                {
                    auto width = static_cast<uint32_t>(LOWORD(lParam));
                    auto height = static_cast<uint32_t>(HIWORD(lParam));

                    WindowResizeEvent event(width, height);
                    window->m_Data.EventCallback(event);
                }
                return 0;
            case WM_KEYDOWN:
            case WM_SYSKEYDOWN:
                if (window->m_Data.EventCallback)
                {
                    auto keycode = static_cast<int>(wParam);
                    bool isRepeat = (lParam & (static_cast<LPARAM>(1) << 30)) != 0;

                    KeyPressedEvent event(keycode, isRepeat);
                    window->m_Data.EventCallback(event);
                }
                return 0;
            case WM_KEYUP:
            case WM_SYSKEYUP:
                if (window->m_Data.EventCallback)
                {
                    auto keycode = static_cast<int>(wParam);

                    KeyReleasedEvent event(keycode);
                    window->m_Data.EventCallback(event);
                }
                return 0;
            case WM_CHAR:
                if (window->m_Data.EventCallback)
                {
                    auto keycode = static_cast<int>(wParam);

                    KeyTypedEvent event(keycode);
                    window->m_Data.EventCallback(event);
                }
                return 0;
            default:
                return DefWindowProc(hWnd, uMsg, wParam, lParam);
            }
        }

        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    Win32Window::Win32Window(const WindowProps& props)
    {
        Init(props);
    }

    Win32Window::~Win32Window()
    {
        Shutdown();
    }

    void Win32Window::OnUpdate()
    {
        MSG msg = {};
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    void Win32Window::SetEventCallback(const EventCallbackFn& callback)
    {
        m_Data.EventCallback = callback;
    }

    void Win32Window::Init(const WindowProps& props)
    {
        m_Data.Height = props.Height;
        m_Data.Width = props.Width;
        m_Data.Title = props.Title;

        m_Instance = GetModuleHandle(nullptr);

        WNDCLASS wc = {};
        wc.lpfnWndProc = WndProc;
        wc.hInstance = m_Instance;
        wc.lpszClassName = L"AlisaWindowClass";

        RegisterClass(&wc);

        m_Window = CreateWindowEx(
            0, L"AlisaWindowClass",
            std::wstring(m_Data.Title.begin(), m_Data.Title.end()).c_str(),
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT,
            static_cast<int>(m_Data.Width),
            static_cast<int>(m_Data.Height),
            nullptr, nullptr,
            m_Instance,
            this
        );

        ShowWindow(m_Window, SW_SHOW);
    }

    void Win32Window::Shutdown()
    {
        DestroyWindow(m_Window);
    }
} // namespace Alisa
