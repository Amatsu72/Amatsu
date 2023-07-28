#include "../pch.h"
#include "Renderer.h"
#include "../Paltform/OpenGL/OpenGLShader.h"

namespace Engine {

	Renderer::SceneData* Renderer::s_scene_data = new Renderer::SceneData;

	void Renderer::init()
	{
		RenderCommand::init();
	}

	void Renderer::on_window_resize(uint32_t width, uint32_t height)
	{
		RenderCommand::set_viewport(0, 0, width, height);
	}

	void Renderer::begin_scene(Camera& camera)
	{
		s_scene_data->view_projection_matrix = camera.get_view_projection_matrix();
	}

	void Renderer::end_scene()
	{
	}

	void Renderer::submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertex_array, const glm::mat4& transform)
	{
		shader->bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->set_mat4("u_viewProjection", s_scene_data->view_projection_matrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->set_mat4("u_transform", transform);
		vertex_array->bind();
		RenderCommand::draw_indexed(vertex_array);
	}

}