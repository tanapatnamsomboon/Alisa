#include "Alisa/Core/Application.h"
#include "Alisa/Core/EntryPoint.h"

#include <print>

class HelloAlisaApp : public Alisa::Application
{
public:
	HelloAlisaApp()
	{
		std::println("Hello Alisa!");
	}

	~HelloAlisaApp() = default;
};

Alisa::Application* Alisa::CreateApplication()
{
	return new HelloAlisaApp;
}