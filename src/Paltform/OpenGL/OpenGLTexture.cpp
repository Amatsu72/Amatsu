#include "../../pch.h"
#include "OpenGLTexture.h"
#include <stb_image.h>

namespace Engine {

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, void* data)
		:m_width(width), m_height(height), m_channels(4)
	{
		m_internal_format = GL_RGBA8;
		m_data_format = GL_RGBA;

		glCreateTextures(GL_TEXTURE_2D, 1, &m_render_id);
		glTextureStorage2D(m_render_id, 1, m_internal_format, m_width, m_height);

		glTextureParameteri(m_render_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_render_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_render_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_render_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

		if (data)
		{
			uint32_t size = m_width * m_height * m_channels;
			set_data(data, size);
		}

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
		m_channels = channels;

		if (m_channels == 4)
		{
			m_internal_format = GL_RGBA8;
			m_data_format = GL_RGBA;
		}
		else if (m_channels == 3)
		{
			m_internal_format = GL_RGB8;
			m_data_format = GL_RGB;
		}

		glCreateTextures(GL_TEXTURE_2D, 1, &m_render_id);
		glTextureStorage2D(m_render_id, 1, m_internal_format, m_width, m_height);

		glTextureParameteri(m_render_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_render_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_render_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_render_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

		set_data(data, m_width * m_height * m_channels);

		stbi_image_free(data);	
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_render_id);
	}

	void OpenGLTexture2D::set_data(void* data, uint32_t size)
	{
		if (size != m_width * m_height * m_channels)
			std::cout << "Data must be entire texture!" << std::endl;
		
		glTextureSubImage2D(m_render_id, 0, 0, 0, m_width, m_height, m_data_format, GL_UNSIGNED_BYTE, data);
	}

	void OpenGLTexture2D::bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_render_id);
	}

}