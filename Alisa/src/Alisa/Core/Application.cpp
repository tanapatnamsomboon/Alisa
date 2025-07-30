#include "Application.h"

#include <cassert>

namespace Alisa
{

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		assert(!s_Instance && "Application already created!");
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

}