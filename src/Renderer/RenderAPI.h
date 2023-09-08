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

		enum class Func
		{
			None = 0,
			NEVER, LESS, LEQUAL, GREATER, GEQUAL, EQUAL, NOTEQUAL, ALWAYS
		};
		enum class Op
		{
			None = 0,
			KEEP, ZERO, REPLACE, INCR, INCR_WRAP, DECR, DECR_WRAP, INVERT
		};

		virtual void init() = 0;
		virtual void set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void clear(bool color, bool depth, bool stencil) = 0;
		virtual void set_clear_color(const glm::vec4& color) = 0;

		virtual void draw_indexed(const std::shared_ptr<VertexArray>& vertexArray, bool cull_face = false) = 0;
		virtual void draw(const std::shared_ptr<VertexArray>& vertexArray, uint32_t count, bool cull_face = false) = 0;

		virtual void draw_indexed_instance(const std::shared_ptr<VertexArray>& vertexArray, uint32_t number, bool cull_face = false) = 0;
		virtual void draw_instance(const std::shared_ptr<VertexArray>& vertexArray, uint32_t count, uint32_t number, bool cull_face = false) = 0;

		virtual void set_stencil_test(bool s) = 0;
		virtual void set_depth_test(bool d) = 0;
		virtual void set_depth_mask(bool d) = 0;
		virtual void set_depth_func(Func func) = 0;

		virtual void set_stencil_func(Func func,int value,unsigned int mask) = 0;
		virtual void set_stencil_mask(unsigned int mask) = 0;
		virtual void set_stencil_op(Op sfail, Op dfail, Op pass) = 0;

		virtual void set_cull_face(bool c) = 0;
		virtual void set_line_mode() = 0;
		inline static API get_API() { return s_API; }
	private:

		static API s_API;
	};

}