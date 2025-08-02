#include "pch.h"
#include "Win32Input.h"

#include "Alisa/Core/Application.h"

namespace Alisa
{
    Win32Input::Win32Input()
    {
    }

    bool Win32Input::IsKeyPressed(const KeyCode keyCode) const
    {
        return GetAsyncKeyState(static_cast<int>(keyCode)) & 0x8000;
    }

    bool Win32Input::IsMouseButtonPressed(const MouseCode mouseCode) const
    {
        return GetAsyncKeyState(static_cast<int>(mouseCode)) & 0x8000;
    }

    float Win32Input::GetMouseX() const
    {
        return GetMousePosition().first;
    }

    float Win32Input::GetMouseY() const
    {
        return GetMousePosition().second;
    }

    std::pair<float, float> Win32Input::GetMousePosition() const
    {
        if (auto window = static_cast<HWND>(Application::Get().GetWindow().GetNativeWindow()))
        {
            POINT p;
            GetCursorPos(&p);
            ScreenToClient(window, &p);
            return { static_cast<float>(p.x), static_cast<float>(p.y) };
        }

        ALISA_CORE_ASSERT(false, "Failed to get native window from application.");
    }
}
