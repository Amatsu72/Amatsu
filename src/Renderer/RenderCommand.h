#pragma once
#include "RenderAPI.h"

namespace Engine {

	class RenderCommand
	{
	public:
		inline static void init()
		{
			s_renderAPI->init();
		}

		inline static void set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			s_renderAPI->set_viewport(x, y, width, height);
		}

		inline static void clear()
		{
			s_renderAPI->clear();
		}

		inline static void set_clear_color(const glm::vec4& color)
		{
			s_renderAPI->set_clear_color(color);
		}

		inline static void draw_indexed(const std::shared_ptr<VertexArray>& vertex_array, uint32_t count = 0)
		{
			s_renderAPI->draw_indexed(vertex_array, count);
		}

	private:
		static RenderAPI* s_renderAPI;
	};
}