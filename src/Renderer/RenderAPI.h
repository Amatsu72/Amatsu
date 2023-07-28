#pragma once
#include <glm.hpp>
#include "VertexArray.h"

namespace Engine {

	class RenderAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};

		virtual void init() = 0;
		virtual void set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void clear() = 0;
		virtual void set_clear_color(const glm::vec4& color) = 0;

		virtual void draw_indexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

		inline static API get_API() { return s_API; }
	private:

		static API s_API;
	};

}