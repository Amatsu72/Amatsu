#include "../pch.h"
#include "Scene.h"
#include <imgui.h>
#include "Renderer.h"

#include "../Event/KeyEvent.h"


namespace Engine {
	Scene::Scene() :m_camera_controller(16.0f / 9.0f, 0.1f, 100.0f)
	{
		//to prepare rendering data
		float vertices[] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f,	1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f,	1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f,	0.0f, 1.0f
		};
		m_vertex_array = VertexArray::create();
		std::shared_ptr<VertexBuffer> vertex_buffer = VertexBuffer::create(vertices, sizeof(vertices));
		
		vertex_buffer->set_layout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float2, "a_TexCoord"}
			});
		m_vertex_array->add_vertex_buffer(vertex_buffer);
		
		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};
		std::shared_ptr<IndexBuffer> index_buffer = IndexBuffer::create(indices, sizeof(indices) / sizeof(uint32_t));
		m_vertex_array->set_index_buffer(index_buffer);
		
		auto test_shader = ShaderLibrary::load("../../../../assets/shaders/Texture.glsl");
		auto model_shader = ShaderLibrary::load("../../../../assets/shaders/Model.glsl");
		TextureLibrary::load("../../../../assets/textures/Checkerboard.png");

		std::dynamic_pointer_cast<OpenGLShader>(test_shader)->bind();
		std::dynamic_pointer_cast<OpenGLShader>(test_shader)->set_int("u_Texture", 0);

		std::dynamic_pointer_cast<OpenGLShader>(model_shader)->bind();
		std::dynamic_pointer_cast<OpenGLShader>(model_shader)->set_int("u_Material.diffuse", 0);

		backpack = std::make_shared<Model>("../../../../assets/models/nanosuit/nanosuit.obj");

	}

	void Scene::on_update(Timestep ts)
	{
		m_camera_controller.update(ts);

		glm::vec4 color(test, 1.0f);
		RenderCommand::set_clear_color(color);
		RenderCommand::clear();

		Renderer::begin_scene(m_camera_controller.get_camera());
		
		auto shader = ShaderLibrary::get("Texture");
		auto texture = TextureLibrary::get("Checkerboard");
		texture->bind();

		auto model_shader = ShaderLibrary::get("Model");
		Renderer::submit(shader, m_vertex_array, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));

		glm::mat4 trans = glm::translate(glm::mat4(1.0f), position);
		Renderer::submit(*backpack, model_shader, trans);
		Renderer::end_scene();
	
	}
	void Scene::ui_render()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("test Color", glm::value_ptr(test));
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