#include <Alisa/Alisa.h>
#include <Alisa/Core/EntryPoint.h>

class HelloAlisaApp final : public Alisa::Application
{
public:
    HelloAlisaApp()
    {
        ALISA_LOG("Hello Alisa!");
    }

    ~HelloAlisaApp() = default;
};

Alisa::Application* Alisa::CreateApplication()
{
    return new HelloAlisaApp;
}
