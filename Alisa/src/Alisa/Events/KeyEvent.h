#pragma once

#include "Alisa/Events/Event.h"
#include "Alisa/Core/KeyCodes.h"

namespace Alisa
{
    class KeyEvent : public Event
    {
    public:
        KeyCode GetKeyCode() const { return m_KeyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

    protected:
        explicit KeyEvent(KeyCode keycode)
            : m_KeyCode(keycode)
        {
        }

        KeyCode m_KeyCode;
    };

    class KeyPressedEvent final : public KeyEvent
    {
    public:
        explicit KeyPressedEvent(KeyCode keycode, bool isRepeat = false)
            : KeyEvent(keycode), m_IsRepeat(isRepeat)
        {
        }

        int GetRepeatCount() const { return m_IsRepeat; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressed: " << KeyCodeToString(m_KeyCode) << " (" << m_IsRepeat << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)

    private:
        bool m_IsRepeat;
    };

    class KeyReleasedEvent final : public KeyEvent
    {
    public:
        explicit KeyReleasedEvent(KeyCode keycode)
            : KeyEvent(keycode)
        {
        }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleased: " << KeyCodeToString(m_KeyCode);
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };

    class CharacterTypedEvent final : public Event
    {
    public:
        explicit CharacterTypedEvent(utf32 character)
            : m_Character(character)
        {
        }

        utf32 GetCharacter() const { return m_Character; }

        // FIXME: Output utf32 character. I cast to char for now
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "CharacterTyped: " << static_cast<char>(m_Character);
            return ss.str();
        }

        EVENT_CLASS_TYPE(CharacterTyped)
        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

    private:
        utf32 m_Character;
    };
}
