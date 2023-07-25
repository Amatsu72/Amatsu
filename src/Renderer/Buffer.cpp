#include "../pch.h"
#include "Buffer.h"

namespace Engine {

	uint32_t shader_data_type_size(ShaderDataType type)
	{
		switch (type)
		{
			case Engine::ShaderDataType::Float:		return 4;
			case Engine::ShaderDataType::Float2:	return 4 * 2;
			case Engine::ShaderDataType::Float3:	return 4 * 3;
			case Engine::ShaderDataType::Float4:	return 4 * 4;
			case Engine::ShaderDataType::Mat3:		return 4 * 3 * 3;
			case Engine::ShaderDataType::Mat4:		return 4 * 4 * 4;
			case Engine::ShaderDataType::Int:		return 4;
			case Engine::ShaderDataType::Int2:		return 4 * 2;
			case Engine::ShaderDataType::Int3:		return 4 * 3;
			case Engine::ShaderDataType::Int4:		return 4 * 4;
			case Engine::ShaderDataType::Bool:		return 1;
		}
		std::cout << "Unknown ShaderDataType!" << std::endl;
		return 0;
	}
	BufferElement::BufferElement(ShaderDataType type, const std::string& name, bool normalized)
		:name(name), type(type), size(shader_data_type_size(type)), offset(0), normalized(normalized) {}

	uint32_t BufferElement::get_component_count() const
	{
		switch (type)
		{
			case Engine::ShaderDataType::Float:		return 1;
			case Engine::ShaderDataType::Float2:	return 2;
			case Engine::ShaderDataType::Float3:	return 3;
			case Engine::ShaderDataType::Float4:	return 4;
			case Engine::ShaderDataType::Mat3:		return 3 * 3;
			case Engine::ShaderDataType::Mat4:		return 4 * 4;
			case Engine::ShaderDataType::Int:		return 1;
			case Engine::ShaderDataType::Int2:		return 2;
			case Engine::ShaderDataType::Int3:		return 3;
			case Engine::ShaderDataType::Int4:		return 4;
			case Engine::ShaderDataType::Bool:		return 1;
		}
		std::cout << "Unknown ShaderDataType!" << std::endl;
		return 0;
	}

	BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements)
		:m_elements(elements)
	{
		calculate_offset_and_stride();
	}

	void BufferLayout::calculate_offset_and_stride()
	{
		uint32_t offset = 0;
		m_stride = 0;
		for (auto& element : m_elements)
		{
			element.offset = offset;
			offset += element.size;
			m_stride += element.size;
		}
	}

	std::shared_ptr<VertexBuffer> VertexBuffer::create(float* vertices, uint32_t size)
	{
		return std::shared_ptr<VertexBuffer>();
	}

	std::shared_ptr<VertexBuffer> VertexBuffer::create(uint32_t size)
	{
		return std::shared_ptr<VertexBuffer>();
	}

	std::shared_ptr<IndexBuffer> IndexBuffer::create(uint32_t* indices, uint32_t count)
	{
		return std::shared_ptr<IndexBuffer>();
	}

}