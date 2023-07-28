#pragma once
#include "Event.h"
#include "../Core/KeyCodes.h"

namespace Engine {

	class KeyEvent :public Event
	{
	public:
		inline KeyCode get_key_code() const { return m_key_code; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(KeyCode key_code) 
			:m_key_code(key_code) {}

		KeyCode m_key_code;
	};

	class KeyPressedEvent :public KeyEvent
	{
	public:
		KeyPressedEvent(KeyCode key_code, int repeat_count)
			:KeyEvent(key_code), m_repeat_count(repeat_count) {}

		inline int get_repeat_count() const { return m_repeat_count; }

		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_key_code << " (" << m_repeat_count << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_repeat_count;
	};

	class KeyReleasedEvent :public KeyEvent
	{
	public:
		KeyReleasedEvent(KeyCode key_code) 
			:KeyEvent(key_code) {}

		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_key_code;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class KeyTypedEvent :public KeyEvent
	{
	public:
		KeyTypedEvent(KeyCode key_code) 
			:KeyEvent(key_code) {}

		std::string to_string() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_key_code;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};

}