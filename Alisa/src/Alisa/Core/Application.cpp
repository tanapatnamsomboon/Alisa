#include "pch.h"
#include "Application.h"

#include <chrono>

namespace Alisa
{
    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        ALISA_CORE_ASSERT(!s_Instance, "Application already exist {}");
        s_Instance = this;

        m_Window = Window::Create();
        m_Window->SetEventCallback(ALISA_BIND_EVENT_FUNC(OnEvent));

        m_Input = Input::Create();
    }

    Application::~Application()
    {
        s_Instance = nullptr;
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(ALISA_BIND_EVENT_FUNC(OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(ALISA_BIND_EVENT_FUNC(OnWindowResize));
        //dispatcher.Dispatch<KeyPressedEvent>(ALISA_BIND_EVENT_FUNC(OnKeyPressed));
        //dispatcher.Dispatch<KeyReleasedEvent>(ALISA_BIND_EVENT_FUNC(OnKeyReleased));

        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
        {
            if (e.m_Handled)
            {
                break;
            }
            (*it)->OnEvent(e);
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer)
    {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

    void Application::Run()
    {
        auto lastTime = std::chrono::high_resolution_clock::now();

        while (m_Running)
        {
            auto now = std::chrono::high_resolution_clock::now();
            const f32 time = std::chrono::duration<f32>(now - lastTime).count();
            lastTime = now;

            TimeStep deltaTime(time);

            for (Layer* layer : m_LayerStack)
            {
                layer->OnUpdate(deltaTime);
            }


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
