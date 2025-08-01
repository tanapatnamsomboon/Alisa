#pragma once

#include "Alisa/Core/Input.h"

namespace Alisa
{
    class Win32Input final : public Input
    {
    public:
        Win32Input();

        bool IsKeyPressed(KeyCode code) const override;
        bool IsMouseButtonPressed(MouseCode button) const override;

        float GetMouseX() const override;
        float GetMouseY() const override;
        std::pair<float, float> GetMousePosition() const override;
    };
}
