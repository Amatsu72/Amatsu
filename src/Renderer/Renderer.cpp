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

	void Renderer::begin_scene(Camera& camera,
		const std::shared_ptr<DirectionalLight>& directional_light,
		const std::vector<std::shared_ptr<PointLight>>& point_lights,
		const std::shared_ptr<SpotLight>& spot_light)
	{
		s_scene_data->view_projection_matrix = camera.get_view_projection_matrix();

		for (auto& [name, shader] : ShaderLibrary::get_all_shaders())
		{
			shader->bind();
			shader->set_float3("u_ViewPosition", camera.get_position());
			if (directional_light)
				directional_light->bind(shader);

			shader->set_int("u_PointLightCount", point_lights.size());

			for (int i = 0; i < point_lights.size(); ++i)
			{
				point_lights[i]->bind(shader, i);
			}
			if (spot_light)
				spot_light->bind(shader);
			
		}
		
	}

	void Renderer::end_scene()
	{
	}

	void Renderer::submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertex_array, const glm::mat4& transform)
	{
		shader->bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->set_mat4("u_ViewProjection", s_scene_data->view_projection_matrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->set_mat4("u_Transform", transform);
		vertex_array->bind();
		if (vertex_array->get_index_buffers())
			RenderCommand::draw_indexed(vertex_array);
		else
			RenderCommand::draw(vertex_array, vertex_array->get_vertex_count());
	}
	
	void Renderer::submit(const Mesh& mesh, const std::shared_ptr<Shader>& shader, const glm::mat4& transform)
	{
		mesh.get_material()->use();
		mesh.get_material()->bind(shader);
		submit(shader, mesh.get_vertex_array(), transform);
	}
	
	void Renderer::submit(const Model& model, const std::shared_ptr<Shader>& shader, const glm::mat4& transform)
	{
		for (const Mesh& mesh : model.get_meshes())
		{
			submit(mesh, shader, transform);
		}
	}

}