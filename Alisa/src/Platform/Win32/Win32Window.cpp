#include "Win32Window.h"

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
                PostQuitMessage(0);
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
