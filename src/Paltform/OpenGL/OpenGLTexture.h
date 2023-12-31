#pragma once
#include "../../Renderer/Texture.h"
#include <glad/glad.h>

namespace Engine {

	class OpenGLTexture2D :public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height, void* data);
		OpenGLTexture2D(const std::string& path);
		OpenGLTexture2D(uint32_t width, uint32_t height, bool msaa, uint32_t samples = 4);
		OpenGLTexture2D(uint32_t width, uint32_t height);
		~OpenGLTexture2D() override;

		uint32_t get_width() const override { return m_width; }
		uint32_t get_height() const override { return m_height; }

		void set_data(void* data, uint32_t size) override;
		void bind(uint32_t slot = 0) const override;

	private:
		std::string m_path;
		uint32_t m_width, m_height, m_channels;
		uint32_t m_render_id;
		GLenum m_internal_format, m_data_format;		
	};

	class OpenGLCubeMap :public CubeMap
	{
	public:
		OpenGLCubeMap(const std::string& folder_path);
		~OpenGLCubeMap() override;

		void bind() const override;

	private:
		uint32_t m_render_id;
	};
			
}