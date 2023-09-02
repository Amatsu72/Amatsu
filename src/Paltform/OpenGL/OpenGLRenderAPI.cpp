#include "../../pch.h"
#include "OpenGLRenderAPI.h"
#include <glad/glad.h>

namespace Engine {

	static GLenum op_to_gl_type(RenderAPI::GLOp op)
	{
		switch (op)
		{
			case Engine::RenderAPI::GLOp::DECR:			return GL_DECR;
			case Engine::RenderAPI::GLOp::DECR_WRAP:	return GL_DECR_WRAP;
			case Engine::RenderAPI::GLOp::INCR:			return GL_INCR;
			case Engine::RenderAPI::GLOp::INCR_WRAP:	return GL_INCR_WRAP;
			case Engine::RenderAPI::GLOp::INVERT:		return GL_INVERT;
			case Engine::RenderAPI::GLOp::KEEP:			return GL_KEEP;
			case Engine::RenderAPI::GLOp::REPLACE:		return GL_REPLACE;
			case Engine::RenderAPI::GLOp::ZERO:			return GL_ZERO;
		}
	}

	static GLenum func_to_gl_type(RenderAPI::GLFunc func)
	{
		switch (func)
		{
			case Engine::RenderAPI::GLFunc::NEVER:		return GL_NEVER;
			case Engine::RenderAPI::GLFunc::LESS:		return GL_LESS;
			case Engine::RenderAPI::GLFunc::LEQUAL:		return GL_LEQUAL;
			case Engine::RenderAPI::GLFunc::GREATER:	return GL_GREATER;
			case Engine::RenderAPI::GLFunc::GEQUAL:		return GL_GEQUAL;
			case Engine::RenderAPI::GLFunc::EQUAL:		return GL_EQUAL;
			case Engine::RenderAPI::GLFunc::NOTEQUAL:	return GL_NOTEQUAL;
			case Engine::RenderAPI::GLFunc::ALWAYS:		return GL_ALWAYS;
		}
	}

	void OpenGLRenderAPI::init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_DEPTH_TEST);
	}

	void OpenGLRenderAPI::set_viewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
	{
		glViewport(x, y, width, height);
	}

	void OpenGLRenderAPI::clear()
	{
		if (m_stencil_test && m_depth_test)
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		else if (m_stencil_test)
			glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		else if (m_depth_test)
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		else
			glClear(GL_COLOR_BUFFER_BIT);
	}

	void OpenGLRenderAPI::set_clear_color(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRenderAPI::draw_indexed(const std::shared_ptr<VertexArray>& vertex_array, bool cull_face)
	{
		if(cull_face)
			glEnable(GL_CULL_FACE);

		uint32_t count = vertex_array->get_index_buffers()->get_count();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		//glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_CULL_FACE);
	}

	void OpenGLRenderAPI::draw(const std::shared_ptr<VertexArray>& vertex_array, uint32_t count, bool cull_face)
	{
		if (cull_face)
			glEnable(GL_CULL_FACE);

		glDrawArrays(GL_TRIANGLES, 0, count);
		//glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_CULL_FACE);
	}

	void OpenGLRenderAPI::draw_indexed_instance(const std::shared_ptr<VertexArray>& vertex_array, uint32_t number, bool cull_face)
	{
		if (cull_face)
			glEnable(GL_CULL_FACE);

		uint32_t count = vertex_array->get_index_buffers()->get_count();
		glDrawElementsInstanced(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr, number);
		//glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_CULL_FACE);
	}

	void OpenGLRenderAPI::draw_instance(const std::shared_ptr<VertexArray>& vertex_array, uint32_t count, uint32_t number, bool cull_face)
	{
		if (cull_face)
			glEnable(GL_CULL_FACE);

		glDrawArraysInstanced(GL_TRIANGLES, 0, count, number);
		//glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_CULL_FACE);
	}

	void OpenGLRenderAPI::set_stencil_test(bool s)
	{
		m_stencil_test = s;

		if (m_stencil_test)
			glEnable(GL_STENCIL_TEST);
		else
			glDisable(GL_STENCIL_TEST);
	}

	void OpenGLRenderAPI::set_depth_test(bool d)
	{
		m_depth_test = d;

		if (m_depth_test)
			glEnable(GL_DEPTH_TEST);
		else
			glDisable(GL_DEPTH_TEST);
	}

	void OpenGLRenderAPI::set_depth_func(GLFunc func)
	{
		glDepthFunc(func_to_gl_type(func));
	}

	void OpenGLRenderAPI::set_depth_mask(bool d)
	{
		if (d)
			glDepthMask(GL_TRUE);
		else
			glDepthMask(GL_FALSE);
	}

	void OpenGLRenderAPI::set_cull_face(bool c)
	{
		m_cull_face = c;

		if (m_cull_face)
			glEnable(GL_CULL_FACE);
		else
			glDisable(GL_CULL_FACE);
	}

	void OpenGLRenderAPI::set_stencil_func(GLFunc func, int value, unsigned int mask)
	{
		glStencilFunc(func_to_gl_type(func), value, mask);
	}

	void OpenGLRenderAPI::set_stencil_mask(unsigned int mask)
	{
		glStencilMask(mask);
	}

	void OpenGLRenderAPI::set_stencil_op(GLOp sfail, GLOp dfail, GLOp pass)
	{
		glStencilOp(op_to_gl_type(sfail), op_to_gl_type(dfail), op_to_gl_type(pass));
	}

	void OpenGLRenderAPI::set_line_mode()
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
}