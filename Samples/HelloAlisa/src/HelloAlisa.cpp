#include "Alisa/Core/EntryPoint.h"

class HelloAlisaApp : public Alisa::Application
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