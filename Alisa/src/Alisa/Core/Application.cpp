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
        ALISA_CORE_INFO("WindowCloseEvent received in Application.");
        m_Running = false;
        return true;
    }

} // namespace Alisa
