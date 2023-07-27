#include "../pch.h"
#include "Texture.h"
#include "Renderer.h"
#include "../Paltform/OpenGL/OpenGLTexture.h"

namespace Engine {

	std::shared_ptr<Texture2D> Texture2D::create(uint32_t width, uint32_t height)
	{
		switch (Renderer::get_API())
		{
			case RenderAPI::API::None:
				std::cout << "RenderAPI::None is currently nor support!" << std::endl;
				return nullptr;
			case RenderAPI::API::OpenGL:
				return std::make_shared<OpenGLTexture2D>(width, height);
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

}