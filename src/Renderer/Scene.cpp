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
		
		auto test_shader = m_shader_library.load("../../../../assets/shaders/Texture.glsl");
		m_texture = Texture2D::create("../../../../assets/textures/Checkerboard.png");
		
		std::dynamic_pointer_cast<OpenGLShader>(test_shader)->bind();
		std::dynamic_pointer_cast<OpenGLShader>(test_shader)->set_int("u_Texture", 0);

		//float test_data[] = {
		//	-0.5f, -0.5f, 0.0f,
		//	 0.5f, -0.5f, 0.0f,
		//	 0.0f,  0.5f, 0.0f
		//};
		//test_va = VertexArray::create();
		//std::shared_ptr<VertexBuffer> vb = VertexBuffer::create(test_data, sizeof(test_data));
		//vb->set_layout({ { ShaderDataType::Float3, "a_Position" } });
		//test_va->add_vertex_buffer(vb);
		//unsigned int index[] = { 0,1,2 };
		//std::shared_ptr<IndexBuffer> ib = IndexBuffer::create(index, sizeof(index) / sizeof(uint32_t));
		//test_va->set_index_buffer(ib);
		//auto shader = m_shader_library.load("../../../../assets/shaders/ColorShader.glsl");

	}

	void Scene::on_update(Timestep ts)
	{
		m_camera_controller.update(ts);

		glm::vec4 color(test, 1.0f);
		RenderCommand::set_clear_color(glm::vec4(0.0f));
		RenderCommand::clear();

		Renderer::begin_scene(m_camera_controller.get_camera());
		
		auto shader = m_shader_library.get("Texture");
		m_texture->bind();
		Renderer::submit(shader, m_vertex_array, glm::scale(glm::mat4(1.0f), glm::vec3(1.0f)));

		//auto test_shader = m_shader_library.get("ColorShader");
		//std::dynamic_pointer_cast<OpenGLShader>(test_shader)->set_float4("u_color", color);
		//Renderer::submit(test_shader, test_va);
		
		Renderer::end_scene();
	
	}
	void Scene::ui_render()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("test Color", glm::value_ptr(test));
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