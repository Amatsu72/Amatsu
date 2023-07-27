#include "../../pch.h"
#include "OpenGLTexture.h"
#include <stb_image.h>

namespace Engine {

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		:m_width(width), m_height(height)
	{
		m_internal_format = GL_RGBA8;
		m_data_format = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_render_id);
		glTextureStorage2D(m_render_id, 1, m_render_id, m_width, m_height);

		glTextureParameteri(m_render_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_render_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_render_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_render_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		:m_path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = nullptr;
		data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		
		if (!data)
			std::cout << "Failed to load image!" << std::endl;
		m_width = width;
		m_height = height;

		GLenum internal_format = 0, data_format = 0;
		if (channels == 4)
		{
			internal_format = GL_RGBA8;
			data_format = GL_RGBA;
		}
		else if (channels == 3)
		{
			internal_format = GL_RGB8;
			data_format = GL_RGB;
		}
		m_internal_format = internal_format;
		m_data_format = data_format;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_render_id);
		glTextureStorage2D(m_render_id, 1, internal_format, m_width, m_height);

		glTextureParameteri(m_render_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_render_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_render_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_render_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTextureSubImage2D(m_render_id, 0, 0, 0, m_width, m_height, data_format, GL_UNSIGNED_BYTE, data);
		
		stbi_image_free(data);
		
	}
	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_render_id);
	}
	void OpenGLTexture2D::set_data(void* data, uint32_t size)
	{
		uint32_t bpp = m_data_format == GL_RGBA ? 4 : 3;
		if (size != m_width * m_height * bpp)
			std::cout << "Data must be entire texture!" << std::endl;
		
		glTextureSubImage2D(m_render_id, 0, 0, 0, m_width, m_height, m_data_format, GL_UNSIGNED_BYTE, data);
	}
	void OpenGLTexture2D::bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_render_id);
	}
}