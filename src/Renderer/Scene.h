#pragma once
#include "../Core/Timestep.h"
#include "CameraController.h"
#include "Texture.h"
#include "VertexArray.h"
#include "../Paltform/OpenGL/OpenGLShader.h"

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
		ShaderLibrary m_shader_library;
		std::shared_ptr<VertexArray> m_vertex_array, test_va;
		std::shared_ptr<Texture2D> m_texture;

		glm::vec3 test;
		CameraController m_camera_controller;
	};

}