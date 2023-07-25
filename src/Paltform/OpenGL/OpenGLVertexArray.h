#pragma once
#include "../../Renderer/VertexArray.h"

namespace Engine {

	class OpenGLVertexArray :public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray() override;

		void bind() const override;
		void unbind() const override;

		void add_vertex_buffer(std::shared_ptr<VertexBuffer>& vertex_buffer) override;
		void set_index_buffer(std::shared_ptr<IndexBuffer>& index_buffer) override;

		const std::vector<std::shared_ptr<VertexBuffer>>& get_vertex_buffers() const override { return m_vertex_buffers; }
		const std::shared_ptr<IndexBuffer>& set_index_buffers() const override { return m_index_buffers; }
	private:
		uint32_t m_render_id;
		std::vector<std::shared_ptr<VertexBuffer>> m_vertex_buffers;
		std::shared_ptr<IndexBuffer> m_index_buffers;
	};
}