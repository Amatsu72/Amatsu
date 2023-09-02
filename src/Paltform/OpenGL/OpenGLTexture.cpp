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

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height, bool msaa, uint32_t samples)
		:m_width(width), m_height(height)
	{
		glGenTextures(1, &m_render_id);
		if (msaa)
		{
			glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_render_id);
			glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, GL_RGB, m_width, m_height, GL_TRUE);
			glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_render_id, 0);
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D, m_render_id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glBindTexture(GL_TEXTURE_2D, 0);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_render_id, 0);
		}
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
	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////

	OpenGLCubeMap::OpenGLCubeMap(const std::string& folder_path)
	{
		glGenTextures(1, &m_render_id);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_render_id);

		std::vector<std::string> textures_path;
		//for (const auto& file : std::filesystem::directory_iterator(folder_path)) 
		//{
		//	if (std::filesystem::is_regular_file(file)) 
		//	{
		//		std::string path = folder_path + file.path().filename().string();
		//		textures_path.push_back(path);
		//	}
		//}
		std::vector<std::string> faces
		{
			"right.jpg",
			"left.jpg",
			"top.jpg",
			"bottom.jpg",
			
			"front.jpg",
			"back.jpg"
		};
		for (int i = 0; i < faces.size(); ++i)
			textures_path.push_back(folder_path + faces[i]);

		int width, height, channels;
		GLenum internal_format, data_format;
		stbi_set_flip_vertically_on_load(0);
		stbi_uc* data;
		for (int i = 0; i < textures_path.size(); i++)
		{
			data = stbi_load(textures_path[i].c_str(), &width, &height, &channels, 0);
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
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internal_format, width, height, 0, data_format, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	}

	OpenGLCubeMap::~OpenGLCubeMap()
	{
		glDeleteTextures(1, &m_render_id);
	}

	void OpenGLCubeMap::bind() const
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_render_id);
	}

}