#include "../pch.h"
#include "Texture.h"
#include "Renderer.h"
#include "../Paltform/OpenGL/OpenGLTexture.h"

namespace Engine {

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

}