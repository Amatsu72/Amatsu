#pragma once
#include "Camera.h"
#include "../Core/Timestep.h"
#include "../Event/ApplicationEvent.h"
#include "../Event/MouseEvent.h"

namespace Engine {

	class CameraController
	{
	public:
		CameraController(float aspect_ratio,float z_near,float z_far);

		void update(Timestep ts);
		void on_event(Event& e);

		inline Camera& get_camera() { return m_camera; }
		inline const Camera& get_camera() const { return m_camera; }

		inline float get_fov() const { return m_fov; }
		void set_camera_postion(glm::vec3& postion);
		glm::mat4 get_projection();

	private:
		bool on_mouse_scrolled(MouseScrolledEvent& e);
		bool on_window_resized(WindowResizeEvent& e);
		bool on_mouse_button_pressed(MouseButtonPressedEvent& e);
		bool on_mouse_button_released(MouseButtonReleasedEvent& e);
		bool on_mouse_moved(MouseMovedEvent& e);

		Camera m_camera;
		glm::vec3 m_camera_position = { 0.0f,0.0f,3.0f };
		float m_aspect_ratio;
		float m_z_near, m_z_far;
		float m_fov = 45.0f;

		float m_movement_speed = 10.0f;
		float m_zoom_speed = 1.0f;
		float m_mouse_speed = 0.1f;

		float m_mouse_lastX = 640;
		float m_mouse_lastY = 360;
		bool first_mouse = true;

		bool MOUSE_BUTTON_STATE = false;
	};

}