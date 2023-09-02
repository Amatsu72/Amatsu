#include "../pch.h"
#include "Renderer.h"
#include "../Paltform/OpenGL/OpenGLShader.h"

namespace Engine {

	Renderer::SceneData* Renderer::s_scene_data = new Renderer::SceneData;
	Renderer::BatchRenderData* Renderer::s_data = new Renderer::BatchRenderData;

	void Renderer::init()
	{
		RenderCommand::init();

		s_data->batch_vertex_array = VertexArray::create();
		s_data->batch_vertex_buffer = VertexBuffer::create(s_data->MaxVertices * sizeof(Vertex));
		s_data->batch_vertex_buffer->set_layout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float3, "a_Normal"},
			{ShaderDataType::Float2, "a_TexCoord"}
			});
		s_data->batch_vertex_array->add_vertex_buffer(s_data->batch_vertex_buffer);

		s_data->vertex_buffer_base = new Vertex[s_data->MaxVertices];

		s_data->batch_shader = Shader::create("../../../../assets/shaders/Box.glsl");
		s_data->batch_texture = Texture2D::create("../../../../assets/textures/container2.png");
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
		s_scene_data->view_matrix = camera.get_view_matrix();
		s_scene_data->projection_matrix = camera.get_projection_matrix();

		s_data->vertex_buffer_ptr = s_data->vertex_buffer_base;

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
		uint32_t data_size = (uint8_t*)s_data->vertex_buffer_ptr - (uint8_t*)s_data->vertex_buffer_base;
		if(data_size)
		{
			s_data->batch_vertex_buffer->set_data(s_data->vertex_buffer_base, data_size);
			s_data->batch_shader->bind();
			std::dynamic_pointer_cast<OpenGLShader>(s_data->batch_shader)->set_mat4("u_Transform", glm::mat4(1.0f));
			s_data->batch_vertex_array->bind();
			s_data->batch_texture->bind();
			RenderCommand::draw(s_data->batch_vertex_array, s_data->batch_vertex_array->get_vertex_count());
		}
	}

	void Renderer::submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertex_array, const glm::mat4& transform, bool cull_face)
	{
		shader->bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->set_mat4("u_Transform", transform);
		vertex_array->bind();
		if (vertex_array->get_index_buffers())
			RenderCommand::draw_indexed(vertex_array, cull_face);
		else
			RenderCommand::draw(vertex_array, vertex_array->get_vertex_count(), cull_face);
	}

	void Renderer::submit_instance(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertex_array, uint32_t number, bool cull_face)
	{
		shader->bind();//?
		vertex_array->bind();
		if (vertex_array->get_index_buffers())
			RenderCommand::draw_indexed_instance(vertex_array, number, cull_face);
		else
			RenderCommand::draw_instance(vertex_array, vertex_array->get_vertex_count(), number, cull_face);
	}

	void Renderer::submit_batch(const std::vector<glm::vec3>& position)
	{
		s_data->batch_shader->bind();
		std::dynamic_pointer_cast<OpenGLShader>(s_data->batch_shader)->set_int("u_Texture", 0);
		for (auto& i : position)
		{
			//face1
			//point1
			s_data->vertex_buffer_ptr->Position = { -0.5f + i.x , -0.5f + i.y, -0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { 0.0f,  0.0f, -1.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 0.0f, 0.0f };
			s_data->vertex_buffer_ptr++;
			//point2
			s_data->vertex_buffer_ptr->Position = { 0.5f + i.x , -0.5f + i.y, -0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { 0.0f,  0.0f, -1.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 1.0f, 0.0f };
			s_data->vertex_buffer_ptr++;
			//point3
			s_data->vertex_buffer_ptr->Position = { 0.5f + i.x , 0.5f + i.y, -0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { 0.0f,  0.0f, -1.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 1.0f, 1.0f };
			s_data->vertex_buffer_ptr++;
			//point4
			s_data->vertex_buffer_ptr->Position = { 0.5f + i.x , 0.5f + i.y, -0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { 0.0f,  0.0f, -1.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 1.0f, 1.0f };
			s_data->vertex_buffer_ptr++;
			//point5
			s_data->vertex_buffer_ptr->Position = { -0.5f + i.x , 0.5f + i.y, -0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { 0.0f,  0.0f, -1.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 0.0f, 1.0f };
			s_data->vertex_buffer_ptr++;
			//point6
			s_data->vertex_buffer_ptr->Position = { -0.5f + i.x , -0.5f + i.y, -0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { 0.0f,  0.0f, -1.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 0.0f, 0.0f };
			s_data->vertex_buffer_ptr++;
	
			//face2
			//point7
			s_data->vertex_buffer_ptr->Position = { -0.5f + i.x , -0.5f + i.y, 0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { 0.0f,  0.0f, 1.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 0.0f, 0.0f };
			s_data->vertex_buffer_ptr++;
			//point8
			s_data->vertex_buffer_ptr->Position = { 0.5f + i.x , -0.5f + i.y, 0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { 0.0f,  0.0f, 1.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 1.0f, 0.0f };
			s_data->vertex_buffer_ptr++;
			//point9
			s_data->vertex_buffer_ptr->Position = { 0.5f + i.x , 0.5f + i.y, 0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { 0.0f,  0.0f, 1.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 1.0f, 1.0f };
			s_data->vertex_buffer_ptr++;
			//point10
			s_data->vertex_buffer_ptr->Position = { 0.5f + i.x , 0.5f + i.y, 0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { 0.0f,  0.0f, 1.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 1.0f, 1.0f };
			s_data->vertex_buffer_ptr++;
			//point11
			s_data->vertex_buffer_ptr->Position = { -0.5f + i.x , 0.5f + i.y, 0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { 0.0f,  0.0f, 1.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 0.0f, 1.0f };
			s_data->vertex_buffer_ptr++;
			//point12
			s_data->vertex_buffer_ptr->Position = { -0.5f + i.x , -0.5f + i.y, 0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { 0.0f,  0.0f, 1.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 0.0f, 0.0f };
			s_data->vertex_buffer_ptr++;

			//face3
			//point13
			s_data->vertex_buffer_ptr->Position = { -0.5f + i.x , 0.5f + i.y, 0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { -1.0f,  0.0f, 0.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 1.0f, 0.0f };
			s_data->vertex_buffer_ptr++;
			//point14
			s_data->vertex_buffer_ptr->Position = { -0.5f + i.x , 0.5f + i.y, -0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { -1.0f,  0.0f, 0.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 1.0f, 1.0f };
			s_data->vertex_buffer_ptr++;
			//point15
			s_data->vertex_buffer_ptr->Position = { -0.5f + i.x , -0.5f + i.y, -0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { -1.0f,  0.0f, 0.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 0.0f, 1.0f };
			s_data->vertex_buffer_ptr++;
			//point16
			s_data->vertex_buffer_ptr->Position = { -0.5f + i.x , -0.5f + i.y, -0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { -1.0f,  0.0f, 0.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 0.0f, 1.0f };
			s_data->vertex_buffer_ptr++;
			//point17
			s_data->vertex_buffer_ptr->Position = { -0.5f + i.x , -0.5f + i.y, 0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { -1.0f,  0.0f, 0.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 0.0f, 0.0f };
			s_data->vertex_buffer_ptr++;
			//point18
			s_data->vertex_buffer_ptr->Position = { -0.5f + i.x , 0.5f + i.y, 0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { -1.0f,  0.0f, 0.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 1.0f, 0.0f };
			s_data->vertex_buffer_ptr++;

			//face4
			//point19
			s_data->vertex_buffer_ptr->Position = { 0.5f + i.x , 0.5f + i.y, 0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { 1.0f,  0.0f, 0.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 1.0f, 0.0f };
			s_data->vertex_buffer_ptr++;
			//point20
			s_data->vertex_buffer_ptr->Position = { 0.5f + i.x , 0.5f + i.y, -0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { 1.0f,  0.0f, 0.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 1.0f, 1.0f };
			s_data->vertex_buffer_ptr++;
			//point21
			s_data->vertex_buffer_ptr->Position = { 0.5f + i.x , -0.5f + i.y, -0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { 1.0f,  0.0f, 0.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 0.0f, 1.0f };
			s_data->vertex_buffer_ptr++;
			//point22
			s_data->vertex_buffer_ptr->Position = { 0.5f + i.x , -0.5f + i.y, -0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { 1.0f,  0.0f, 0.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 0.0f, 1.0f };
			s_data->vertex_buffer_ptr++;
			//point23
			s_data->vertex_buffer_ptr->Position = { 0.5f + i.x , -0.5f + i.y, 0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { 1.0f,  0.0f, 0.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 0.0f, 0.0f };
			s_data->vertex_buffer_ptr++;
			//point24
			s_data->vertex_buffer_ptr->Position = { 0.5f + i.x , 0.5f + i.y, 0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { 1.0f,  0.0f, 0.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 1.0f, 0.0f };
			s_data->vertex_buffer_ptr++;

			//face5
			//point25
			s_data->vertex_buffer_ptr->Position = { -0.5f + i.x , -0.5f + i.y, -0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { 0.0f,  -1.0f, 0.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 0.0f, 0.0f };
			s_data->vertex_buffer_ptr++;
			//point26
			s_data->vertex_buffer_ptr->Position = { 0.5f + i.x , -0.5f + i.y, -0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { 0.0f,  -1.0f, 0.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 1.0f, 0.0f };
			s_data->vertex_buffer_ptr++;
			//point27
			s_data->vertex_buffer_ptr->Position = { 0.5f + i.x , -0.5f + i.y, 0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { 0.0f,  -1.0f, 0.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 1.0f, 1.0f };
			s_data->vertex_buffer_ptr++;
			//point28
			s_data->vertex_buffer_ptr->Position = { 0.5f + i.x , -0.5f + i.y, 0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { 0.0f,  -1.0f, 0.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 1.0f, 1.0f };
			s_data->vertex_buffer_ptr++;
			//point29
			s_data->vertex_buffer_ptr->Position = { -0.5f + i.x , -0.5f + i.y, 0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { 0.0f,  -1.0f, 0.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 0.0f, 1.0f };
			s_data->vertex_buffer_ptr++;
			//point30
			s_data->vertex_buffer_ptr->Position = { -0.5f + i.x , -0.5f + i.y, -0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { 0.0f,  -1.0f, 0.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 0.0f, 0.0f };
			s_data->vertex_buffer_ptr++;

			//face6
			//point31
			s_data->vertex_buffer_ptr->Position = { -0.5f + i.x , 0.5f + i.y, -0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { 0.0f,  1.0f, 0.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 0.0f, 0.0f };
			s_data->vertex_buffer_ptr++;
			//point32
			s_data->vertex_buffer_ptr->Position = { 0.5f + i.x , 0.5f + i.y, -0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { 0.0f,  1.0f, 0.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 1.0f, 0.0f };
			s_data->vertex_buffer_ptr++;
			//point33
			s_data->vertex_buffer_ptr->Position = { 0.5f + i.x , 0.5f + i.y, 0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { 0.0f,  1.0f, 0.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 1.0f, 1.0f };
			s_data->vertex_buffer_ptr++;
			//point34
			s_data->vertex_buffer_ptr->Position = { 0.5f + i.x , 0.5f + i.y, 0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { 0.0f,  1.0f, 0.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 1.0f, 1.0f };
			s_data->vertex_buffer_ptr++;
			//point35
			s_data->vertex_buffer_ptr->Position = { -0.5f + i.x , 0.5f + i.y, 0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { 0.0f,  1.0f, 0.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 0.0f, 1.0f };
			s_data->vertex_buffer_ptr++;
			//point36
			s_data->vertex_buffer_ptr->Position = { -0.5f + i.x , 0.5f + i.y, -0.5f + i.z, };
			s_data->vertex_buffer_ptr->Normal = { 0.0f,  1.0f, 0.0f };
			s_data->vertex_buffer_ptr->TexCoord = { 0.0f, 0.0f };
			s_data->vertex_buffer_ptr++;
		}
	}
	
	void Renderer::submit(const Mesh& mesh, const std::shared_ptr<Shader>& shader, const glm::mat4& transform, bool cull_face)
	{
		mesh.get_material()->use();
		mesh.get_material()->bind(shader);
		submit(shader, mesh.get_vertex_array(), transform, cull_face);
	}
	
	void Renderer::submit(const Model& model, const std::shared_ptr<Shader>& shader, const glm::mat4& transform, bool cull_face)
	{
		for (const Mesh& mesh : model.get_meshes())
		{
			submit(mesh, shader, transform, cull_face);
		}
	}

	void Renderer::submit_instance(const Model& model, const std::shared_ptr<Shader>& shader, uint32_t number, bool cull_face)
	{
		for (const Mesh& mesh : model.get_meshes())
		{
			mesh.get_material()->use();
			mesh.get_material()->bind(shader);
			submit_instance(shader, mesh.get_vertex_array(), number, cull_face);
		}
	}

}