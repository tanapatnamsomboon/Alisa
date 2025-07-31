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
    }

    Application::~Application()
    {
        s_Instance = nullptr;
    }

    void Application::Run()
    {
        while (m_Running)
        {
            m_Window->OnUpdate();
        }
    }
} // namespace Alisa
