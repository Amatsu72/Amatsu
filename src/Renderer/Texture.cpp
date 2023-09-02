#include "../pch.h"
#include "Texture.h"
#include "Renderer.h"
#include "../Paltform/OpenGL/OpenGLTexture.h"

namespace Engine {

	TextureLibrary* TextureLibrary::s_instance = new TextureLibrary();

	std::shared_ptr<Texture2D> Texture2D::create(uint32_t width, uint32_t height, void* data)
	{
		switch (Renderer::get_API())
		{
			case RenderAPI::API::None:
				std::cout << "RenderAPI::None is currently nor support!" << std::endl;
				return nullptr;
			case RenderAPI::API::OpenGL:
				return std::make_shared<OpenGLTexture2D>(width, height, data);
		}
		std::cout << "Unkonwn RenderAPI!" << std::endl;
		return nullptr;
	}

	std::shared_ptr<Texture2D> Texture2D::create(const std::string& path)
	{
		switch (Renderer::get_API())
		{
			case RenderAPI::API::None:
				std::cout << "RenderAPI::None is currently nor support!" << std::endl;
				return nullptr;
			case RenderAPI::API::OpenGL:
				return std::make_shared<OpenGLTexture2D>(path);
		}
		std::cout << "Unkonwn RenderAPI!" << std::endl;
		return nullptr;
	}

	std::shared_ptr<Texture2D> Texture2D::create_flat_color(const glm::vec4& color)
	{
		uint32_t flat_color_data =
			(uint32_t)(color.a * 255) << 24 |
			(uint32_t)(color.b * 255) << 16 |
			(uint32_t)(color.g * 255) << 8 |
			(uint32_t)(color.r * 255);
		return Texture2D::create(1, 1, &flat_color_data);
	}

	std::shared_ptr<Texture2D> Texture2D::create_attachment(uint32_t width, uint32_t height, bool msaa, uint32_t samples)
	{
		return std::make_shared<OpenGLTexture2D>(width, height, msaa, samples);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////

	std::shared_ptr<CubeMap> CubeMap::create(const std::string& folder_path)
	{
		switch (Renderer::get_API())
		{
		case RenderAPI::API::None:
			std::cout << "RenderAPI::None is currently nor support!" << std::endl;
			return nullptr;
		case RenderAPI::API::OpenGL:
			return std::make_shared<OpenGLCubeMap>(folder_path);
		}
		std::cout << "Unkonwn RenderAPI!" << std::endl;
		return nullptr;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////

	void TextureLibrary::add(const std::string& name, const std::shared_ptr<Texture2D>& texture)
	{
		if (exists_impl(name))
		{
			std::cout << name <<"   :texture already exists!" << std::endl;
			return;
		}
		m_textures[name] = texture;
	}

	std::shared_ptr<Texture2D> TextureLibrary::load_impl(const std::string& filepath)
	{
		auto texture = Texture2D::create(filepath);

		auto last_slash = filepath.find_last_of("/\\");
		last_slash = last_slash == std::string::npos ? 0 : last_slash + 1;
		auto last_dot = filepath.rfind('.');
		auto count = last_dot == std::string::npos ? filepath.size() - last_slash : last_dot - last_slash;
		std::string name = filepath.substr(last_slash, count);

		add(name, texture);
		return texture;
	}

	std::shared_ptr<Texture2D> TextureLibrary::load_impl(const std::string& name, const std::string& filepath)
	{
		auto texture = Texture2D::create(filepath);
		add(name, texture);
		return texture;
	}

	std::shared_ptr<Texture2D> TextureLibrary::get_impl(const std::string& name)
	{
		if (!exists_impl(name))
		{
			std::cout << name << "    :texture not found!" << std::endl;
			return std::shared_ptr<Texture2D>();
		}
		return m_textures[name];
	}

	bool TextureLibrary::exists_impl(const std::string& name) const
	{
		return m_textures.find(name) != m_textures.end();
	}

}