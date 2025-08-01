#pragma once

#include "Alisa/Core/Base.h"
#include "Alisa/Core/Window.h"
#include "Alisa/Events/Event.h"
#include "Alisa/Events/ApplicationEvent.h"
#include "Alisa/Events/KeyEvent.h"

int main(int argc, char** argv);

namespace Alisa
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        virtual void OnEvent(Event& e);

        Window& GetWindow() const { return *m_Window; }

        static Application& Get() { return *s_Instance; }

    private:
        void Run();

        bool OnWindowClose(WindowCloseEvent& e);
        bool OnWindowResize(WindowResizeEvent& e);
        bool OnKeyPressed(KeyPressedEvent& e);
        bool OnKeyReleased(KeyReleasedEvent& e);

    private:
        Scope<Window> m_Window;
        bool m_Running = true;
        bool m_Minimized = false;

    private:
        static Application* s_Instance;
        friend int ::main(int argc, char** argv);
    };

    Application* CreateApplication();
} // namespace Alisa
