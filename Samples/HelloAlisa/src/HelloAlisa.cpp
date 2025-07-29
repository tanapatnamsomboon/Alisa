#include "Alisa/Core/Application.h"
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

int main(int argc, char** argv)
{
	auto app = Alisa::CreateApplication();

	app->Run();

	delete app;

	return 0;
}