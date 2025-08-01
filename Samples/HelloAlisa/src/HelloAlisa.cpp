#include <Alisa/Alisa.h>
#include <Alisa/Core/EntryPoint.h>

class HelloLayer : public Alisa::Layer
{
public:
    HelloLayer()
        : Layer("Hello Alisa")
    {}

    void OnUpdate(Alisa::TimeStep ts) override
    {
    }

    void OnEvent(Alisa::Event& e) override
    {
        if (Alisa::Application::Get().GetInput().IsKeyPressed(Alisa::KeyCode::Space))
        {
            ALISA_CORE_TRACE("Space!");
        }
    }
};

class HelloAlisaApp final : public Alisa::Application
{
public:
    HelloAlisaApp()
    {
        ALISA_LOG("Hello Alisa!");
        PushLayer(new HelloLayer());
    }

    ~HelloAlisaApp() = default;
};

Alisa::Application* Alisa::CreateApplication()
{
    return new HelloAlisaApp;
}
