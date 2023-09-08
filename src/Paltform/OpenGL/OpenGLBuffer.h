#pragma once
#include "../../Renderer/Buffer.h"

namespace Engine {

	class OpenGLVertexBuffer :public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(glm::mat4* instance_matrix, uint32_t size);
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

	class OpenGLFrameBuffer :public FrameBuffer
	{
	public:
		OpenGLFrameBuffer(uint32_t width, uint32_t height);
		~OpenGLFrameBuffer() override;

		void check() override;
		void bind() const override;
		void unbind() const override;
		void blit() override;
		void attach(const std::shared_ptr<Texture2D>& texture) override;
		void texture_bind(uint32_t index = 0) override;
	private:
		uint32_t m_render_id;
		uint32_t m_width, m_height;
		std::vector<std::shared_ptr<Texture2D>> m_textures;
	};

	class OpenGLUniformBuffer :public UniformBuffer
	{
	public:
		OpenGLUniformBuffer(const BufferLayout& layout, uint32_t index);
		~OpenGLUniformBuffer() override;
		
		void set_int(int value, uint32_t offset) override;
		void set_float(float value, uint32_t offset) override;
		void set_float3(const glm::vec3& value, uint32_t offset) override;
		void set_float4(const glm::vec4& value, uint32_t offset) override;
		void set_mat4(const glm::mat4& value, uint32_t offset) override;

		const BufferLayout& get_layout() const override { return m_layout; }

	private:
		BufferLayout m_layout;
		uint32_t m_render_id;
	};

	class OpenGLRenderBuffer :public RenderBuffer
	{
	public:
		OpenGLRenderBuffer(uint32_t width, uint32_t height, bool msaa, uint32_t samples = 4);
		~OpenGLRenderBuffer() override;

		void bind() const override;
		void unbind() const override;

		void attach_frame_buffer() override;
	private:
		uint32_t m_render_id;
		uint32_t m_width, m_height;
	};
}