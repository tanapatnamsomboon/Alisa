#pragma once

#include "Alisa/Core/Base.h"
#include <string>

namespace Alisa
{
	struct WindowProps
	{
		std::string Title;
		uint32_t Width, Height;

		WindowProps(const std::string& title = "Alisa Engine",
					uint32_t width = 1600,
					uint32_t height = 900)
			: Title(title), Width(width), Height(height)
		{ }
	};

	class Window
	{
	public:
		virtual ~Window() = default;
		
		virtual void OnUpdate() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		static Scope<Window> Create(const WindowProps& props = WindowProps());
	};
}