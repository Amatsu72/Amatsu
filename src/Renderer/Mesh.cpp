#include "../pch.h"
#include "Mesh.h"

namespace Engine {

	void Mesh::setup_mesh()
	{
		m_vertex_array = VertexArray::create();
		m_vertex_buffer = VertexBuffer::create(reinterpret_cast<float*>(m_vertices.data()), (uint32_t)m_vertices.size() * sizeof(Vertex));
		m_vertex_buffer->set_layout({
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float3, "a_Normal"},
			{ShaderDataType::Float2, "a_TexCoord"}
			});
		m_index_buffer = IndexBuffer::create(reinterpret_cast<uint32_t*>(m_indices.data()), 
			(uint32_t)m_indices.size() * sizeof(Index) / sizeof(uint32_t));

		m_vertex_array->add_vertex_buffer(m_vertex_buffer);
		m_vertex_array->set_index_buffer(m_index_buffer);

		m_vertex_array->unbind();
	}

	void Mesh::move_mesh(Mesh&& other)
	{
		m_vertices = std::move(other.m_vertices);
		m_indices = std::move(other.m_indices);
		m_material = std::move(other.m_material);

		m_vertex_array = std::move(other.m_vertex_array);
		m_vertex_buffer = std::move(other.m_vertex_buffer);
		m_index_buffer = std::move(other.m_index_buffer);
	}
}