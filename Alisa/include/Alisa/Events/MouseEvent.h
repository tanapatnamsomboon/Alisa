#pragma once

#include "Alisa/Events/Event.h"
#include "Alisa/Core/MouseCodes.h"

namespace Alisa
{
    class MouseMovedEvent final : public Event
    {
    public:
        MouseMovedEvent(const f32 x, const f32 y)
            : m_MouseX(x), m_MouseY(y)
        {
        }

        f32 GetX() const { return m_MouseX; }
        f32 GetY() const { return m_MouseY; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        f32 m_MouseX;
        f32 m_MouseY;
    };

    class MouseScrolledEvent final : public Event
    {
    public:
        MouseScrolledEvent(const f32 xOffset, const f32 yOffset)
            : m_XOffset(xOffset), m_YOffset(yOffset)
        {
        }

        f32 GetXOffset() const { return m_XOffset; }
        f32 GetYOffset() const { return m_YOffset; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        f32 m_XOffset;
        f32 m_YOffset;
    };

    class MouseButtonEvent : public Event
    {
    public:
        MouseCode GetMouseCode() const { return m_MouseCode; }

        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)

    protected:
        explicit MouseButtonEvent(MouseCode mouseCode)
            : m_MouseCode(mouseCode)
        {
        }

        MouseCode m_MouseCode;
    };

    class MouseButtonPressedEvent final : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(MouseCode mouseCode)
            : MouseButtonEvent(mouseCode)
        {
        }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << MouseCodeToString(m_MouseCode);
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class MouseButtonReleasedEvent final : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(MouseCode mouseCode)
            : MouseButtonEvent(mouseCode)
        {
        }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << MouseCodeToString(m_MouseCode);
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };
}
