#pragma once
#include "../Core/Timestep.h"
#include "CameraController.h"
#include "Texture.h"
#include "VertexArray.h"
#include "../Paltform/OpenGL/OpenGLShader.h"
#include "Model.h"
#include "Light.h"

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
		std::shared_ptr<VertexArray> floor_vertex_array;
		std::shared_ptr<Model> model;

		std::shared_ptr<DirectionalLight> directional_light;

		std::shared_ptr<SpotLight> spot_light;

		std::vector<std::shared_ptr<PointLight>> point_lights;
		std::shared_ptr<VertexArray> point_vertex_array;
		glm::vec3 point_light_positions[4];

		glm::vec3 direcitonal_color = { 1.0, 1.0, 1.0 };

		glm::vec3 position = { 0,-10,-30 };

		CameraController m_camera_controller;
	};

}