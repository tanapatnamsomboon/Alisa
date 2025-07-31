#pragma once

#include "Alisa/Events/Event.h"

namespace Alisa
{
    class WindowCloseEvent final : public Event
    {
    public:
        WindowCloseEvent() = default;

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)
    };

    class WindowResizeEvent final : public Event
    {
    public:
        WindowResizeEvent(const uint32_t width, const uint32_t height)
            : m_Width(width), m_Height(height)
        {
        }

        uint32_t GetWidth() const { return m_Width; }
        uint32_t GetHeight() const { return m_Height; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResize: " << m_Width << ", " << m_Height;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(EventCategoryApplication)

    private:
        uint32_t m_Width;
        uint32_t m_Height;
    };
}
