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
			const glm::mat4& transform = glm::mat4(1.0f));

		static void submit(const Mesh& mesh, const std::shared_ptr<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));
		static void submit(const Model& model, const std::shared_ptr<Shader>& shader, const glm::mat4& transform = glm::mat4(1.0f));

		inline static RenderAPI::API get_API() { return RenderAPI::get_API(); }

	private:
		struct SceneData {
			glm::mat4 view_projection_matrix;
		};
		static SceneData* s_scene_data;
	};

}