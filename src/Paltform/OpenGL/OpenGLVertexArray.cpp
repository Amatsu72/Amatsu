#include "../../pch.h"
#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace Engine {

	static GLenum shader_data_type_to_opengl_base_type(ShaderDataType type)
	{
		switch (type)
		{	
			case Engine::ShaderDataType::Float:			return GL_FLOAT;
			case Engine::ShaderDataType::Float2:		return GL_FLOAT;
			case Engine::ShaderDataType::Float3:		return GL_FLOAT;
			case Engine::ShaderDataType::Float4:		return GL_FLOAT;
			case Engine::ShaderDataType::Mat3:			return GL_FLOAT;
			case Engine::ShaderDataType::Mat4:			return GL_FLOAT;
			case Engine::ShaderDataType::Int:			return GL_INT;
			case Engine::ShaderDataType::Int2:			return GL_INT;
			case Engine::ShaderDataType::Int3:			return GL_INT;
			case Engine::ShaderDataType::Int4:			return GL_INT;
			case Engine::ShaderDataType::Bool:			return GL_BOOL;
		}
		std::cout << "Unknown ShaderDataType!" << std::endl;
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_render_id);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_render_id);
	}
	void OpenGLVertexArray::bind() const
	{
		glBindVertexArray(m_render_id);
	}
	void OpenGLVertexArray::unbind() const
	{
		glBindVertexArray(0);
	}
	void OpenGLVertexArray::add_vertex_buffer(std::shared_ptr<VertexBuffer>& vertex_buffer)
	{
		if (vertex_buffer->get_layout().get_elements().size() == 0)
			std::cout << "Vertex Buffer has no layout!" << std::endl;

		glBindVertexArray(m_render_id);
		vertex_buffer->bind();

		uint32_t index = 0;
		const auto& layout = vertex_buffer->get_layout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index, element.get_component_count(),
				shader_data_type_to_opengl_base_type(element.type),
				element.normalized ? GL_TRUE : GL_FALSE,
				layout.get_stride(), (const void*)element.offset);
			++index;
		}
		m_vertex_buffers.push_back(vertex_buffer);
	}
	void OpenGLVertexArray::set_index_buffer(std::shared_ptr<IndexBuffer>& index_buffer)
	{
		glBindVertexArray(m_render_id);
		index_buffer->bind();
		m_index_buffers = index_buffer;
	}

}