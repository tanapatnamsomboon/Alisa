#include "pch.h"
#include "Application.h"

namespace Alisa
{
    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        ALISA_CORE_ASSERT(!s_Instance, "Application already exist {}");
        s_Instance = this;

        m_Window = Window::Create();
        m_Window->SetEventCallback([this](Event& e)
            {
                this->OnEvent(e);
            }
        );
    }

    Application::~Application()
    {
        s_Instance = nullptr;
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        //dispatcher.Dispatch<WindowCloseEvent>(ALISA_BIND_EVENT_FUNC(OnWindowClose));
        //dispatcher.Dispatch<WindowResizeEvent>(ALISA_BIND_EVENT_FUNC(OnWindowResize));
        //dispatcher.Dispatch<KeyPressedEvent>(ALISA_BIND_EVENT_FUNC(OnKeyPressed));
        //dispatcher.Dispatch<KeyReleasedEvent>(ALISA_BIND_EVENT_FUNC(OnKeyReleased));
    }

    void Application::Run()
    {
        while (m_Running)
        {
            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent& e)
    {
        uint32_t width = e.GetWidth();
        uint32_t height = e.GetHeight();

        if (width == 0 || height == 0)
        {
            m_Minimized = true;
            return false;
        }

        m_Minimized = false;

        return false;
    }

    bool Application::OnKeyPressed(KeyPressedEvent& e)
    {
        KeyCode keycode = e.GetKeyCode();

        return false;
    }

    bool Application::OnKeyReleased(KeyReleasedEvent& e)
    {
        KeyCode keycode = e.GetKeyCode();

        return false;
    }

} // namespace Alisa
