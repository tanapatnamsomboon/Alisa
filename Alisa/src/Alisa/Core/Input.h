#pragma once

#include "Alisa/Core/Base.h"
#include "Alisa/Core/KeyCodes.h"
#include "Alisa/Core/MouseCodes.h"

namespace Alisa
{
    class Input
    {
    public:
        virtual ~Input() = default;

        virtual bool IsKeyPressed(KeyCode keyCode) const = 0;
        virtual bool IsMouseButtonPressed(MouseCode mouseCode) const = 0;

        virtual float GetMouseX() const = 0;
        virtual float GetMouseY() const = 0;
        virtual std::pair<float, float> GetMousePosition() const = 0;

        static Scope<Input> Create();
    };
}
