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
        dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& ev)
            {
                return OnWindowClose(ev);
            }
        );
        dispatcher.Dispatch<WindowResizeEvent>([this](WindowResizeEvent& ev)
            {
                return OnWindowResize(ev);
            }
        );
        dispatcher.Dispatch<KeyPressedEvent>([this](KeyPressedEvent& ev)
            {
                return OnKeyPressed(ev);
            }
        );
        dispatcher.Dispatch<KeyReleasedEvent>([this](KeyReleasedEvent& ev)
            {
                return OnKeyReleased(ev);
            }
        );
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
        // ALISA_CORE_INFO("Application received WindowCloseEvent. Initiating shutdown...");
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent& e)
    {
        uint32_t width = e.GetWidth();
        uint32_t height = e.GetHeight();

        // ALISA_CORE_INFO("Application received WindowResizeEvent: {}x{}", width, height);

        if (width == 0 || height == 0)
        {
            m_Minimized = true;
            // ALISA_CORE_INFO("Window minimized.");
            return false;
        }

        m_Minimized = false;

        return false;
    }

    bool Application::OnKeyPressed(KeyPressedEvent& e)
    {
        int keycode = e.GetKeyCode();

        //ALISA_CORE_INFO("Application received KeyPressedEvent: {}", keycode);

        return false;
    }

    bool Application::OnKeyReleased(KeyReleasedEvent& e)
    {
        int keycode = e.GetKeyCode();

        //ALISA_CORE_INFO("Application received KeyReleasedEvent: {}", keycode);

        return false;
    }

} // namespace Alisa
