#pragma once
#include "KeyCodes.h"

namespace Engine {

	class Input
	{
	public:
		static bool is_key_pressed(KeyCode keycode);
		static bool is_key_released(KeyCode keycode);

		static bool is_mouse_button_pressed(MouseButton button);
		static bool is_mouse_button_released(MouseButton button);

		static float get_mouseX();
		static float get_mouseY();
		static std::pair<float, float> get_mouse_position();
	};

}