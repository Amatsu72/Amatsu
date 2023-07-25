#pragma once
#include "../Core/Timestep.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "CameraController.h"

namespace Engine {

	class Scene
	{
	public:
		Scene();
		~Scene(){}

		void on_update(Timestep ts);

		void ui_render();

		void on_event();
	private:
		glm::vec3 test;
		CameraController m_camera_controller;
	};
}