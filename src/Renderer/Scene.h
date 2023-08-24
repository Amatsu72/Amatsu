#pragma once
#include "../Core/Timestep.h"
#include "CameraController.h"
#include "Texture.h"
#include "VertexArray.h"
#include "../Paltform/OpenGL/OpenGLShader.h"
#include "Model.h"

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
		std::shared_ptr<VertexArray> m_vertex_array;
		std::shared_ptr<Model> backpack;

		glm::vec3 test;
		glm::vec3 position = { 0,-10,-30 };

		CameraController m_camera_controller;
	};

}