#pragma once
#include <glm.hpp>
#include "Material.h"
#include "VertexArray.h"
#include "Buffer.h"

namespace Engine {

	struct Vertex {
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoord;
	};

	struct Index {
		uint32_t v1, v2, v3;
	};

	class Mesh
	{
	public:
		Mesh(const std::vector<Vertex>& vertices, const std::vector<Index>& indices, const std::shared_ptr<Material>& material = nullptr)
			:m_vertices(vertices), m_indices(indices), m_material(material)
		{
			setup_mesh();
		}

		Mesh(Mesh&& other)
		{
			move_mesh(std::move(other));
		}
		
		Mesh& operator=(Mesh&& other)
		{
			move_mesh(std::move(other));
			return *this;
		}

		inline std::shared_ptr<Material> get_material() const { return m_material; }
		inline std::shared_ptr<VertexArray> get_vertex_array() const { return m_vertex_array; }

	private:
		void setup_mesh();
		void move_mesh(Mesh&& other);

		std::vector<Vertex> m_vertices;
		std::vector<Index> m_indices;
		std::shared_ptr<Material> m_material;

		std::shared_ptr<VertexArray> m_vertex_array;
		std::shared_ptr<VertexBuffer> m_vertex_buffer;
		std::shared_ptr<IndexBuffer> m_index_buffer;
	};
}