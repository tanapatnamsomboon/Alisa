#pragma once

#include "Alisa/Core/Base.h"
#include <string>

namespace Alisa
{
    struct WindowProps
    {
        std::string Title;
        u32         Width;
        u32         Height;

        WindowProps(const std::string& title  = "Alisa Engine", u32 width  = 1600, u32 height = 900)
            : Title(title), Width(width), Height(height)
        {
        }
    };

    class Event;

    using EventCallbackFn = std::function<void(Event&)>;

    class Window
    {
    public:
        virtual ~Window() = default;

        virtual void OnUpdate() = 0;

        virtual u32 GetWidth() const = 0;
        virtual u32 GetHeight() const = 0;

        virtual void* GetNativeWindow() const = 0;

        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

        static Scope<Window> Create(const WindowProps& props = WindowProps());
    };
} // namespace Alisa
