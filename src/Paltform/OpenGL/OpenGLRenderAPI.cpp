#include "../../pch.h"
#include "OpenGLRenderAPI.h"
#include <glad/glad.h>

namespace Engine {

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
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderAPI::set_clear_color(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRenderAPI::draw_indexed(const std::shared_ptr<VertexArray>& vertex_array, uint32_t index_count)
	{
		//uint32_t count = index_count ? index_count : vertex_array->get_index_buffers()->get_count();
		uint32_t count = vertex_array->get_index_buffers()->get_count();
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
		//glBindTexture(GL_TEXTURE_2D, 0);
	}

	void OpenGLRenderAPI::draw(const std::shared_ptr<VertexArray>& vertex_array, uint32_t count)
	{
		glDrawArrays(GL_TRIANGLES, 0, count);
	}

}