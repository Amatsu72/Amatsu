#pragma once
#include "Buffer.h"

namespace Engine {

	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual void add_vertex_buffer(std::shared_ptr<VertexBuffer>& vertex_buffer) = 0;
		virtual void set_index_buffer(std::shared_ptr<IndexBuffer>& index_buffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& get_vertex_buffers() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& set_index_buffers() const = 0;

		static std::shared_ptr<VertexArray> create();
	};

}