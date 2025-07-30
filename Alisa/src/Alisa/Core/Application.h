#pragma once

#include "Alisa/Core/Base.h"
#include "Alisa/Core/Window.h"

int main(int argc, char** argv);

namespace Alisa
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

	private:
		void Run();

	private:
		Scope<Window> m_Window;
		bool m_Running = true;

	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);
	};

	Application* CreateApplication();
}