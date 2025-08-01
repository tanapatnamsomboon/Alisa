#pragma once

#include "Alisa/Core/Base.h"

namespace Alisa
{
    enum class EventType
    {
        None = 0,
        WindowClose, WindowResize,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum EventCategory
    {
        None = 0,
        EventCategoryApplication = ALISA_BIT(0),
        EventCategoryInput       = ALISA_BIT(1),
        EventCategoryKeyboard    = ALISA_BIT(2),
        EventCategoryMouse       = ALISA_BIT(3),
        EventCategoryMouseButton = ALISA_BIT(4)
    };

    class Event
    {
    public:
        virtual EventType   GetEventType() const     = 0;
        virtual const char* GetName() const          = 0;
        virtual i32         GetCategoryFlags() const = 0;
        virtual std::string ToString() const  { return GetName(); }

        bool IsInCategory(EventCategory category) const
        {
            return GetCategoryFlags() & category;
        }

        bool m_Handled = false;
    };

    class EventDispatcher
    {
    public:
        explicit EventDispatcher(Event& event)
            : m_Event(event)
        {
        }

        template<typename T, typename F>
        bool Dispatch(const F& func)
        {
            if (m_Event.GetEventType() == T::GetStaticType())
            {
                m_Event.m_Handled |= func(static_cast<T&>(m_Event));
                return true;
            }
            return false;
        }

    private:
        Event& m_Event;
    };

#   define EVENT_CLASS_TYPE(type) \
        static EventType GetStaticType() { return EventType::type; } \
        virtual EventType GetEventType() const override { return GetStaticType(); } \
        virtual const char* GetName() const override { return #type; }

#   define EVENT_CLASS_CATEGORY(category) \
        virtual i32 GetCategoryFlags() const override { return category; }
}
