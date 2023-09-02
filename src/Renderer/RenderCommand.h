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

		inline static void draw_indexed(const std::shared_ptr<VertexArray>& vertex_array, bool cull_face = false)
		{
			s_renderAPI->draw_indexed(vertex_array, cull_face);
		}
		inline static void draw(const std::shared_ptr<VertexArray>& vertex_array, uint32_t count, bool cull_face = false)
		{
			s_renderAPI->draw(vertex_array, count, cull_face);
		}

		inline static void draw_indexed_instance(const std::shared_ptr<VertexArray>& vertex_array, uint32_t number, bool cull_face = false)
		{
			s_renderAPI->draw_indexed_instance(vertex_array, number, cull_face);
		}
		inline static void draw_instance(const std::shared_ptr<VertexArray>& vertex_array, uint32_t count, uint32_t number, bool cull_face = false)
		{
			s_renderAPI->draw_instance(vertex_array, count, number, cull_face);
		}

		inline static void set_stencil_test(bool s)
		{
			s_renderAPI->set_stencil_test(s);
		}
		inline static void set_depth_test(bool d)
		{
			s_renderAPI->set_depth_test(d);
		}
		inline static void set_stencil_func(RenderAPI::GLFunc func, int value, unsigned int mask)
		{
			s_renderAPI->set_stencil_func(func, value, mask);
		}
		inline static void set_stencil_mask(unsigned int mask)
		{
			s_renderAPI->set_stencil_mask(mask);
		}
		inline static void set_stencil_op(RenderAPI::GLOp sfail, RenderAPI::GLOp dfail, RenderAPI::GLOp pass)
		{
			s_renderAPI->set_stencil_op(sfail, dfail, pass);
		}
		inline static void set_cull_face(bool c)
		{
			s_renderAPI->set_cull_face(c);
		}
		inline static void set_line_mode()
		{
			s_renderAPI->set_line_mode();
		}
		inline static void set_depth_mask(bool d)
		{
			s_renderAPI->set_depth_mask(d);
		}
		inline static void set_depth_func(RenderAPI::GLFunc func)
		{
			s_renderAPI->set_depth_func(func);
		}

	private:
		static RenderAPI* s_renderAPI;
	};

}