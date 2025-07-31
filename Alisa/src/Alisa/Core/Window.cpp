#include "pch.h"
#include "Window.h"

#include "Alisa/Platform/Win32/Win32Window.h"

namespace Alisa
{
    Scope<Window> Window::Create( const WindowProps& props )
    {
#	ifdef ALISA_PLATFORM_WINDOWS
        return CreateScope<Win32Window>(props);
#	else
        return nullptr;
#	endif
    }
} // namespace Alisa
