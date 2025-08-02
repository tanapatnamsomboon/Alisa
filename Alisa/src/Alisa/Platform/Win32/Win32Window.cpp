#include "pch.h"
#include "Win32Window.h"

#include "Alisa/Events/ApplicationEvent.h"
#include "Alisa/Events/KeyEvent.h"
#include "Alisa/Events/MouseEvent.h"

#include <Windowsx.h>

namespace Alisa
{
    // FIXME: Currently can not handle left and right shift, alt, ctrl.
    // it receive VK_SHIFT, VK_ALT, VK_CTRL instead
    LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        if (uMsg == WM_NCCREATE)
        {
            const auto* const createStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
            if (createStruct && createStruct->lpCreateParams)
            {
                SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(createStruct->lpCreateParams));
                return TRUE;
            }
            return FALSE;
        }

        const auto* window = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
        if (!window)
        {
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }

        const auto& eventCallback = window->m_Data.EventCallback;
        if (!eventCallback)
        {
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }

        switch (uMsg)
        {
        case WM_CLOSE:
        {
            WindowCloseEvent event;
            eventCallback(event);

            return 0;
        }
        case WM_SIZE:
        {
            const auto width = static_cast<u32>(LOWORD(lParam));
            const auto height = static_cast<u32>(HIWORD(lParam));

            WindowResizeEvent event(width, height);
            eventCallback(event);

            return 0;
        }
        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        {
            const auto keyCode = static_cast<KeyCode>(wParam);
            bool isRepeat = (lParam & (1ULL << 30)) != 0;

            KeyPressedEvent event(keyCode, isRepeat);
            eventCallback(event);

            return 0;
        }
        case WM_KEYUP:
        case WM_SYSKEYUP:
        {
            const auto keyCode = static_cast<KeyCode>(wParam);

            KeyReleasedEvent event(keyCode);
            eventCallback(event);

            return 0;
        }
        case WM_CHAR:
        {
            const auto character = static_cast<utf32>(wParam);

            CharacterTypedEvent event(character);
            eventCallback(event);

            return 0;
        }
        case WM_MOUSEMOVE:
        {
            const auto x = static_cast<f32>(static_cast<short>(GET_X_LPARAM(lParam)));
            const auto y = static_cast<f32>(static_cast<short>(GET_Y_LPARAM(lParam)));

            MouseMovedEvent event(x, y);
            eventCallback(event);

            return 0;
        }
        case WM_MOUSEWHEEL:
        {
            f32 delta = GET_WHEEL_DELTA_WPARAM(wParam) / static_cast<f32>(WHEEL_DELTA);

            MouseScrolledEvent event(0.0f, delta);
            eventCallback(event);

            return 0;
        }
        case WM_LBUTTONDOWN:
        {
            SetCapture(hWnd);

            MouseButtonPressedEvent event(MouseCode::ButtonLeft);
            eventCallback(event);

            return 0;
        }
        case WM_RBUTTONDOWN:
        {
            MouseButtonPressedEvent event(MouseCode::ButtonRight);
            eventCallback(event);

            return 0;
        }
        case WM_MBUTTONDOWN:
        {
            MouseButtonPressedEvent event(MouseCode::ButtonMiddle);
            eventCallback(event);

            return 0;
        }
        case WM_XBUTTONDOWN:
        {
            const WORD xButton = GET_XBUTTON_WPARAM(wParam);
            MouseCode mouseCode = MouseCode::Unknown;

            switch (xButton)
            {
            case XBUTTON1:
                mouseCode = MouseCode::Button4;
                break;
            case XBUTTON2:
                mouseCode = MouseCode::Button5;
                break;
            default:
                // Unknown X button (Newer mice may have additional buttons) let Windows handle.
                return DefWindowProc(hWnd, uMsg, wParam, lParam);
            }

            MouseButtonPressedEvent event(mouseCode);
            eventCallback(event);

            return TRUE;
        }
        case WM_LBUTTONUP:
        {
            ReleaseCapture();

            MouseButtonReleasedEvent event(MouseCode::ButtonLeft);
            eventCallback(event);

            return 0;
        }
        case WM_RBUTTONUP:
        {
            MouseButtonReleasedEvent event(MouseCode::ButtonRight);
            eventCallback(event);

            return 0;
        }
        case WM_MBUTTONUP:
        {
            MouseButtonReleasedEvent event(MouseCode::ButtonMiddle);
            eventCallback(event);

            return 0;
        }
        case WM_XBUTTONUP:
        {
            const WORD xButton = GET_XBUTTON_WPARAM(wParam);
            MouseCode mouseCode = MouseCode::Unknown;

            switch (xButton)
            {
            case XBUTTON1:
                mouseCode = MouseCode::Button4;
                break;
            case XBUTTON2:
                mouseCode = MouseCode::Button5;
                break;
            default:
                // Unknown X button (Newer mice may have additional buttons) let Windows handle.
                return DefWindowProc(hWnd, uMsg, wParam, lParam); 
            }

            MouseButtonReleasedEvent event(mouseCode);
            eventCallback(event);

            return TRUE;
        }
        case WM_DESTROY:
        {
            WindowCloseEvent event;
            eventCallback(event);

            PostQuitMessage(0);
            return 0;
        }
        case WM_ACTIVATE:
        {
            const bool isActivated = (LOWORD(wParam) != WA_INACTIVE);
            // Window focus events here
            break;
        }
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }

        // It should not have reached to this point.
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
