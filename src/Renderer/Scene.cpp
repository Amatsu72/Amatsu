#include "../pch.h"
#include "Scene.h"
#include <imgui.h>
#include "Renderer.h"

#include "../Event/KeyEvent.h"


namespace Engine {
	Scene::Scene() :m_camera_controller(16.0f / 9.0f, 0.1f, 100.0f)
	{
		//to prepare rendering data
		float planeVertices[] = {
			-20.5f, -10.1f, -50.5f,  0.0f, 0.0f,
			 20.5f, -10.1f, -50.5f,  2.0f, 0.0f,
			 20.5f, -10.1f, -10.5f,  2.0f, 2.0f,
			 20.5f, -10.1f, -10.5f,  2.0f, 2.0f,
			-20.5f, -10.1f, -10.5f,  0.0f, 2.0f,
			-20.5f, -10.1f, -50.5f,  0.0f, 0.0f
		};
		floor_vertex_array = VertexArray::create();
		std::shared_ptr<VertexBuffer> vertex_buffer = VertexBuffer::create(planeVertices, sizeof(planeVertices));
		
		vertex_buffer->set_layout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float2, "a_TexCoord"}
			});
		floor_vertex_array->add_vertex_buffer(vertex_buffer);
		
		//unsigned int indices[] = {
		//	0, 1, 2,
		//	2, 3, 0
		//};
		//std::shared_ptr<IndexBuffer> index_buffer = IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t));
		//m_vertex_array->set_index_buffer(index_buffer);
		float light_vertices[] = {
			-0.1f, -0.1f, -0.1f,
			 0.1f, -0.1f, -0.1f,
			 0.1f,  0.1f, -0.1f,
			 0.1f,  0.1f, -0.1f,
			-0.1f,  0.1f, -0.1f,
			-0.1f, -0.1f, -0.1f,

			-0.1f, -0.1f,  0.1f,
			 0.1f, -0.1f,  0.1f,
			 0.1f,  0.1f,  0.1f,
			 0.1f,  0.1f,  0.1f,
			-0.1f,  0.1f,  0.1f,
			-0.1f, -0.1f,  0.1f,

			-0.1f,  0.1f,  0.1f,
			-0.1f,  0.1f, -0.1f,
			-0.1f, -0.1f, -0.1f,
			-0.1f, -0.1f, -0.1f,
			-0.1f, -0.1f,  0.1f,
			-0.1f,  0.1f,  0.1f,

			 0.1f,  0.1f,  0.1f,
			 0.1f,  0.1f, -0.1f,
			 0.1f, -0.1f, -0.1f,
			 0.1f, -0.1f, -0.1f,
			 0.1f, -0.1f,  0.1f,
			 0.1f,  0.1f,  0.1f,

			-0.1f, -0.1f, -0.1f,
			 0.1f, -0.1f, -0.1f,
			 0.1f, -0.1f,  0.1f,
			 0.1f, -0.1f,  0.1f,
			-0.1f, -0.1f,  0.1f,
			-0.1f, -0.1f, -0.1f,

			-0.1f,  0.1f, -0.1f,
			 0.1f,  0.1f, -0.1f,
			 0.1f,  0.1f,  0.1f,
			 0.1f,  0.1f,  0.1f,
			-0.1f,  0.1f,  0.1f,
			-0.1f,  0.1f, -0.1f
		};
		point_vertex_array = VertexArray::create();
		std::shared_ptr<VertexBuffer> point_vertex_buffer = VertexBuffer::create(light_vertices, sizeof(light_vertices));
		point_vertex_buffer->set_layout({
			{ShaderDataType::Float3, "a_Position"}
			});
		point_vertex_array->add_vertex_buffer(point_vertex_buffer);

		point_light_positions[0] = glm::vec3(0.7f, 0.2f, 2.0f);
		point_light_positions[1] = glm::vec3(2.3f, -3.3f, -4.0f);
		point_light_positions[2] = glm::vec3(-4.0f, 2.0f, -12.0f);
		point_light_positions[3] = glm::vec3(0.0f, 0.0f, -3.0f);

		auto floor_shader = ShaderLibrary::load("../../../../assets/shaders/Texture.glsl");
		auto model_shader = ShaderLibrary::load("../../../../assets/shaders/Model.glsl");
		auto light_shader = ShaderLibrary::load("../../../../assets/shaders/Light.glsl");
		TextureLibrary::load("../../../../assets/textures/marble.jpg");

		std::dynamic_pointer_cast<OpenGLShader>(light_shader)->bind();
		std::dynamic_pointer_cast<OpenGLShader>(light_shader)->set_float4("u_color", glm::vec4(1.0f));
		std::dynamic_pointer_cast<OpenGLShader>(light_shader)->set_int("u_PointLightCount", 4);

		std::dynamic_pointer_cast<OpenGLShader>(floor_shader)->bind();
		std::dynamic_pointer_cast<OpenGLShader>(floor_shader)->set_int("u_Texture", 0);

		model = std::make_shared<Model>("../../../../assets/models/nanosuit/nanosuit.obj");

		directional_light = std::make_shared<DirectionalLight>(direcitonal_color, glm::vec3(1.0, 0, 0), 0.1, 1.0, 1.0);
		for (int i = 0; i < 4; ++i)
			point_lights.push_back(std::make_shared<PointLight>(glm::vec3(1.0), point_light_positions[i], 0.1, 1.0, 1.0));
		spot_light = std::make_shared<SpotLight>(glm::vec3(1.0),
			m_camera_controller.get_camera().get_position(),
			m_camera_controller.get_camera().get_front(), 
			0.1, 1.0, 1.0, glm::cos(glm::radians(12.5f)),
			glm::cos(glm::radians(12.5f + 5.0f)));
	}

	void Scene::on_update(Timestep ts)
	{
		m_camera_controller.update(ts);

		RenderCommand::set_clear_color(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
		RenderCommand::clear();

		Renderer::begin_scene(m_camera_controller.get_camera(), directional_light, point_lights, spot_light);
		directional_light->set_color(direcitonal_color);
		spot_light->set_position(m_camera_controller.get_camera().get_position());
		spot_light->set_direction(m_camera_controller.get_camera().get_front());

		auto shader = ShaderLibrary::get("Texture");
		auto texture = TextureLibrary::get("marble");
		texture->bind();
		Renderer::submit(shader, floor_vertex_array, glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 1.0f, 2.0f)));

		auto light_shader = ShaderLibrary::get("Light");
		for (int i = 0; i < 4; ++i)
		{
			Renderer::submit(light_shader, point_vertex_array, glm::translate(glm::mat4(1.0f), point_light_positions[i]));
		}
		auto model_shader = ShaderLibrary::get("Model");
		
		glm::mat4 trans = glm::translate(glm::mat4(1.0f), position);
		Renderer::submit(*model, model_shader, trans);
		Renderer::end_scene();
	
	}
	void Scene::ui_render()
	{
		static bool show = true;
		//ImGui::ShowDemoWindow(&show);
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("direcitonal Color", glm::value_ptr(direcitonal_color));
		ImGui::DragFloat3("model position", glm::value_ptr(position));

		ImGui::End();
		
	}
	void Scene::on_event(Event& event)
	{
		/*
		if (event.get_event_type() == EventType::KeyPressed)
		{
			KeyPressedEvent& e = (KeyPressedEvent&)event;
			std::cout << (char)e.get_key_code() << std::endl;
		}
		*/
		m_camera_controller.on_event(event);
		
	}
}