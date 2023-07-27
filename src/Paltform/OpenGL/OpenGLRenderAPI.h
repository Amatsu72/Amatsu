#pragma once
#include "../../Renderer/RenderAPI.h"

namespace Engine {

	class OpenGLRenderAPI :public RenderAPI
	{
	public:
		void init() override;
		void set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;

		void clear() override;
		void set_clear_color(const glm::vec4& color) override;
		
		void draw_indexed(const std::shared_ptr<VertexArray>& vertex_array, uint32_t index_count = 0) override;
	};

}