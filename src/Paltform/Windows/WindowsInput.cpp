#include "../../pch.h"
#include "../../Core/Input.h"
#include <GLFW/glfw3.h>
#include "../../Core/Application.h"

namespace Engine{

	bool Input::is_key_pressed(KeyCode keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::get().get_window().get_native_window());
		auto state = glfwGetKey(window, static_cast<int32_t>(keycode));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::is_key_released(KeyCode keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::get().get_window().get_native_window());
		auto state = glfwGetKey(window, static_cast<int32_t>(keycode));
		return state == GLFW_RELEASE;
	}

	bool Input::is_mouse_button_pressed(MouseButton button)
	{
		auto window = static_cast<GLFWwindow*>(Application::get().get_window().get_native_window());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	bool Input::is_mouse_button_released(MouseButton button)
	{
		auto window = static_cast<GLFWwindow*>(Application::get().get_window().get_native_window());
		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_RELEASE;
	}

	float Input::get_mouseX()
	{
		auto [x, y] = get_mouse_position();
		return x;
	}

	float Input::get_mouseY()
	{
		auto [x, y] = get_mouse_position();
		return y;
	}

	std::pair<float, float> Input::get_mouse_position()
	{
		auto window = static_cast<GLFWwindow*>(Application::get().get_window().get_native_window());
		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);
		return { (float)xPos,(float)yPos };
	}

}
