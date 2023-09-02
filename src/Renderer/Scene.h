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
		//model
		std::shared_ptr<Model> model;
		std::shared_ptr<Model> planet;
		std::shared_ptr<Model> rock;
		//light
		std::shared_ptr<DirectionalLight> directional_light;
		std::shared_ptr<SpotLight> spot_light;
		std::vector<std::shared_ptr<PointLight>> point_lights;
		//position
		glm::vec3 point_light_positions[4];
		glm::vec3 vegetation[5];
		std::map<float, glm::vec3> sorted;
		glm::vec3 position = { 0,-10,-30 };
		//light pros
		glm::vec3 direcitonal_color = { 1.0, 1.0, 1.0 };
		glm::vec3 direction = { 1.0,0,0 };
		//camera
		CameraController m_camera_controller;
		//fbo
		std::shared_ptr<FrameBuffer> frame_buffer;
		//skybox
		std::shared_ptr<CubeMap> sky_box;
		//window
		uint32_t m_width, m_height;
		//uniform buffer
		std::shared_ptr<UniformBuffer> uniform_buffer;
		bool draw_outlining = false;
		bool use_frame_buffer = false;
		bool instance = false;
		bool use_msaa = false;
		bool blinn = false;
		bool use_sky_box = false;
		bool batch_render = false;

		glm::mat4* modelMatrices;
		unsigned int amount = 10000;
	};

}