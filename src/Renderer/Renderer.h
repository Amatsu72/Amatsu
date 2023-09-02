#pragma once
#include "RenderCommand.h"
#include "Camera.h"
#include "Shader.h"
#include "Model.h"
#include "Light.h"

namespace Engine {

	class Renderer
	{
	public:
		static void init();
		static void on_window_resize(uint32_t width, uint32_t height);

		static void begin_scene(Camera& camera,
			const std::shared_ptr<DirectionalLight>& directional_light = nullptr,
			const std::vector<std::shared_ptr<PointLight>>& point_lights = {},
			const std::shared_ptr<SpotLight>& spot_light = nullptr);
		static void end_scene();

		static void submit(const std::shared_ptr<Shader>& shader,
			const std::shared_ptr<VertexArray>& vertex_array,
			const glm::mat4& transform = glm::mat4(1.0f),
			bool cull_face = false);

		static void submit_instance(const std::shared_ptr<Shader>& shader,
			const std::shared_ptr<VertexArray>& vertex_array,
			uint32_t number, bool cull_face = false);
		static void submit_batch(const std::vector<glm::vec3>& position);

		static void submit(const Mesh& mesh, const std::shared_ptr<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f), bool cull_face = false);
		static void submit(const Model& model, const std::shared_ptr<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f), bool cull_face = false);
		static void submit_instance(const Model& model, const std::shared_ptr<Shader>& shader, uint32_t number, bool cull_face = false);

		inline static RenderAPI::API get_API() { return RenderAPI::get_API(); }

	private:
		struct SceneData {
			glm::mat4 view_projection_matrix;
			glm::mat4 view_matrix;
			glm::mat4 projection_matrix;
		};
		static SceneData* s_scene_data;	

		struct BatchRenderData
		{
			const uint32_t MaxNum = 100;
			const uint32_t MaxVertices = MaxNum * 36;
			//const uint32_t MaxIndices = MaxNum * 6;

			std::shared_ptr<VertexArray> batch_vertex_array;
			std::shared_ptr<VertexBuffer> batch_vertex_buffer;
			std::shared_ptr<Shader> batch_shader;
			std::shared_ptr<Texture2D> batch_texture;

			Vertex* vertex_buffer_base = nullptr;
			Vertex* vertex_buffer_ptr = nullptr;
		};
		static BatchRenderData* s_data;
		
	};

}