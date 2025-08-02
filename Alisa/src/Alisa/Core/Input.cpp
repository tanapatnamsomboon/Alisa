#include "pch.h"
#include "Alisa/Core/Input.h"

#include "Alisa/Platform/Win32/Win32Input.h"

namespace Alisa
{
    // TODO: Create separation conditions for each platform.
    Scope<Input> Input::Create()
    {
        return CreateScope<Win32Input>();
    }
}
