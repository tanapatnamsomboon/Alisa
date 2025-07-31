#pragma once

#include "Alisa/Core/Base.h"
#include "Alisa/Core/Window.h"
#include "Alisa/Events/Event.h"
#include "Alisa/Events/ApplicationEvent.h"

int main(int argc, char** argv);

namespace Alisa
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        virtual void OnEvent(Event& e);

    private:
        void Run();

        bool OnWindowClose(WindowCloseEvent& e);

    private:
        Scope<Window> m_Window;
        bool m_Running = true;

    private:
        static Application* s_Instance;
        friend int ::main(int argc, char** argv);
    };

    Application* CreateApplication();
} // namespace Alisa
