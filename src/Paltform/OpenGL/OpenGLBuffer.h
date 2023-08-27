#pragma once
#include "../../Renderer/Buffer.h"

namespace Engine {

	class OpenGLVertexBuffer :public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		OpenGLVertexBuffer(uint32_t size);
		~OpenGLVertexBuffer() override;
		
		void bind() const override;
		void unbind() const override;

		void set_data(const void* data, uint32_t size) override;

		const BufferLayout& get_layout() const override { return m_layout; }
		void set_layout(const BufferLayout& layout) override;

		uint32_t get_vertex_count() const override { return m_vertex_count; }
	private:
		uint32_t m_render_id;
		BufferLayout m_layout;
		uint32_t m_vertex_count;
		uint32_t m_size;
	};

	class OpenGLIndexBuffer :public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		~OpenGLIndexBuffer() override;

		void bind() const override;
		void unbind() const override;

		uint32_t get_count() const override { return m_count; }

	private:
		uint32_t m_render_id;
		uint32_t m_count;
	};

}