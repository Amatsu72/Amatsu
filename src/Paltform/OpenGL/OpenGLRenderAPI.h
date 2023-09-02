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
		
		void draw_indexed(const std::shared_ptr<VertexArray>& vertex_array, bool cull_face = false) override;
		void draw(const std::shared_ptr<VertexArray>& vertex_array, uint32_t count, bool cull_face = false) override;
		void draw_indexed_instance(const std::shared_ptr<VertexArray>& vertex_array, uint32_t number, bool cull_face = false) override;
		void draw_instance(const std::shared_ptr<VertexArray>& vertex_array, uint32_t count, uint32_t number, bool cull_face = false) override;
	
		void set_depth_test(bool d) override;
		void set_depth_mask(bool d) override;
		void set_depth_func(GLFunc func) override;
		
		void set_stencil_test(bool s) override;
		void set_stencil_func(GLFunc func, int value, unsigned int mask) override;
		void set_stencil_mask(unsigned int mask) override;
		void set_stencil_op(GLOp sfail, GLOp dfail, GLOp pass) override;

		void set_cull_face(bool c) override;
		void set_line_mode() override;
	private:
		bool m_stencil_test = false;
		bool m_depth_test = true;
		bool m_cull_face = false;
	};

}