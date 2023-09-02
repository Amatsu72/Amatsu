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
		virtual const std::shared_ptr<IndexBuffer>& get_index_buffers() const = 0;

		virtual uint32_t get_vertex_count() const = 0;
		virtual void add_instance_buffer_mat4(std::shared_ptr<VertexBuffer>& vertex_buffer) = 0;

		static std::shared_ptr<VertexArray> create();
	};

	class VertexArrayLibrary
	{
	public:
		static std::shared_ptr<VertexArray> load(const std::string& name)
		{
			return s_instance->load_impl(name);
		}
		static std::shared_ptr<VertexArray> get(const std::string& name)
		{
			return s_instance->get_impl(name);
		}

	private:
		void add(const std::string& name, const std::shared_ptr<VertexArray>& vertex_array);
		std::shared_ptr<VertexArray> load_impl(const std::string& name);
		std::shared_ptr<VertexArray> get_impl(const std::string& name);
		bool exists(const std::string& name) const;

		std::unordered_map<std::string, std::shared_ptr<VertexArray>> m_vertex_arrays;

		static VertexArrayLibrary* s_instance;

	};
}