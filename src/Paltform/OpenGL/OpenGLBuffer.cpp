#include "../../pch.h"
#include "OpenGLBuffer.h"
#include <glad/glad.h>
#include <gtc/type_ptr.hpp>

namespace Engine {

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		glCreateBuffers(1, &m_render_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_render_id);
		glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
		m_size = size;
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
	{
		glCreateBuffers(1, &m_render_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_render_id);
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
		m_size = size;
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(glm::mat4* instance_matrix, uint32_t size)
	{
		glCreateBuffers(1, &m_render_id);
		glBindBuffer(GL_ARRAY_BUFFER, m_render_id);
		glBufferData(GL_ARRAY_BUFFER, size, &instance_matrix[0], GL_STATIC_DRAW);
		m_size = size;
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &m_render_id);
	}

	void OpenGLVertexBuffer::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_render_id);
	}

	void OpenGLVertexBuffer::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLVertexBuffer::set_data(const void* data, uint32_t size)
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_render_id);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
	}

	void OpenGLVertexBuffer::set_layout(const BufferLayout& layout)
	{
		m_layout = layout;
		m_vertex_count = m_size / layout.get_stride();
	}

	///////////////////////////////////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		:m_count(count)
	{
		glCreateBuffers(1, &m_render_id);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_render_id);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
	}
	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_render_id);
	}
	void OpenGLIndexBuffer::bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_render_id);
	}
	void OpenGLIndexBuffer::unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	OpenGLFrameBuffer::OpenGLFrameBuffer(uint32_t width, uint32_t height)
		:m_width(width), m_height(height)
	{
		glGenFramebuffers(1, &m_render_id);
		glBindFramebuffer(GL_FRAMEBUFFER, m_render_id);
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_render_id);
	}

	void OpenGLFrameBuffer::check()
	{
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::bind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_render_id);
	}

	void OpenGLFrameBuffer::unbind() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::blit()
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_render_id);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glBlitFramebuffer(0, 0, m_width, m_height, 0, 0, m_width, m_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	}

	void OpenGLFrameBuffer::attach(const std::shared_ptr<Texture2D>& texture)
	{
		m_textures.push_back(texture);
	}

	void OpenGLFrameBuffer::texture_bind(uint32_t index)
	{
		for (int i = 0; i < m_textures.size(); i++)
			m_textures[i]->bind(i + index);
	}
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////

	OpenGLUniformBuffer::OpenGLUniformBuffer(const BufferLayout& layout, uint32_t index)
	{
		uint32_t size = layout.get_stride();
		glGenBuffers(1, &m_render_id);
		glBindBuffer(GL_UNIFORM_BUFFER, m_render_id);
		glBufferData(GL_UNIFORM_BUFFER, size, NULL, GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		glBindBufferRange(GL_UNIFORM_BUFFER, index, m_render_id, 0, size);
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		glDeleteBuffers(1, &m_render_id);
	}

	void OpenGLUniformBuffer::set_int(int value, uint32_t offset)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_render_id);
		glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(int), &value);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void OpenGLUniformBuffer::set_float(float value, uint32_t offset)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_render_id);
		glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(float), &value);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void OpenGLUniformBuffer::set_float3(const glm::vec3& value, uint32_t offset)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_render_id);
		glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(glm::vec3), glm::value_ptr(value));
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void OpenGLUniformBuffer::set_float4(const glm::vec4& value, uint32_t offset)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_render_id);
		glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(glm::vec4), glm::value_ptr(value));
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void OpenGLUniformBuffer::set_mat4(const glm::mat4& value, uint32_t offset)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, m_render_id);
		glBufferSubData(GL_UNIFORM_BUFFER, offset, sizeof(glm::mat4), glm::value_ptr(value));
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////

	OpenGLRenderBuffer::OpenGLRenderBuffer(uint32_t width, uint32_t height, bool msaa, uint32_t samples)
		:m_width(width), m_height(height)
	{
		glGenRenderbuffers(1, &m_render_id);
		glBindRenderbuffer(GL_RENDERBUFFER, m_render_id);

		if (msaa)
			glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, GL_DEPTH24_STENCIL8, m_width, m_height);
		else
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);

		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	OpenGLRenderBuffer::~OpenGLRenderBuffer()
	{
		glDeleteRenderbuffers(1, &m_render_id);
	}

	void OpenGLRenderBuffer::bind() const
	{
		glBindRenderbuffer(GL_RENDERBUFFER, m_render_id);
	}

	void OpenGLRenderBuffer::unbind() const
	{
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}

	void OpenGLRenderBuffer::attach_frame_buffer()
	{
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_render_id);
	}

}
