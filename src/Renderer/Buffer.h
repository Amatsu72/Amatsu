#pragma once

namespace Engine {

	enum class ShaderDataType
	{
		None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
	};

	static uint32_t shader_data_type_size(ShaderDataType type);

	struct BufferElement {
		std::string name;
		ShaderDataType type;
		uint32_t size;
		uint32_t offset;
		bool normalized = false;

		BufferElement() = default;
		BufferElement(ShaderDataType type, const std::string& name, bool normalized = false);
		uint32_t get_component_count() const;
	};

	class BufferLayout
	{
	public:
		BufferLayout(){}
		BufferLayout(const std::initializer_list<BufferElement>& elements);

		inline uint32_t get_stride() const { return m_stride; }
		inline const std::vector<BufferElement>& get_elements() const { return m_elements; }

		std::vector<BufferElement>::iterator begin() { return m_elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_elements.end(); }

	private:
		void calculate_offset_and_stride();
		
		std::vector<BufferElement> m_elements;
		uint32_t m_stride = 0;
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual const BufferLayout& get_layout() const = 0;
		virtual void set_layout(const BufferLayout& layout) = 0;

		virtual void set_data(const void* data, uint32_t size) = 0;

		static std::shared_ptr<VertexBuffer> create(float* vertices, uint32_t size);
		static std::shared_ptr<VertexBuffer> create(uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void bind() const = 0;
		virtual void unbind() const = 0;

		virtual uint32_t get_count() const = 0;

		static std::shared_ptr<IndexBuffer> create(uint32_t* indices, uint32_t count);
	};

}