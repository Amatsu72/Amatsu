#pragma once
#include "../Core/Timestep.h"
#include "CameraController.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

namespace Engine {

	class Scene
	{
	public:
		Scene();
		~Scene(){}

		void on_update(Timestep ts);

		void ui_render();

		void on_event(Event& e);
	private:
		glm::vec3 test;
		CameraController m_camera_controller;
	};
}