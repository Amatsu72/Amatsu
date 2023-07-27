#include "../pch.h"
#include "Shader.h"
#include "Renderer.h"
#include "../Paltform/OpenGL/OpenGLShader.h"

namespace Engine {

	std::shared_ptr<Shader> Shader::create(const std::string& filepath)
	{
		switch (Renderer::get_API())
		{
			case RenderAPI::API::None:
				std::cout << "RenderAPI::None is currently nor support!" << std::endl;
				return nullptr;
			case RenderAPI::API::OpenGL:
				return std::make_shared<OpenGLShader>(filepath);
		}
		std::cout << "Unkonwn RenderAPI!" << std::endl;
		return nullptr;
	}
	std::shared_ptr<Shader> Shader::create(const std::string& name, const std::string& vertex_src, const std::string& fragment_src)
	{
		switch (Renderer::get_API())
		{
			case RenderAPI::API::None:
				std::cout << "RenderAPI::None is currently nor support!" << std::endl;
				return nullptr;
			case RenderAPI::API::OpenGL:
				return std::make_shared<OpenGLShader>(name, vertex_src, fragment_src);
		}
		std::cout << "Unkonwn RenderAPI!" << std::endl;
		return nullptr;
	}
}