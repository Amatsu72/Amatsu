#include "../pch.h"
#include "Shader.h"
#include "Renderer.h"
#include "../Paltform/OpenGL/OpenGLShader.h"

namespace Engine {

	ShaderLibrary* ShaderLibrary::s_instance = new ShaderLibrary();

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

	
	/// //////////////////////////////////////////////////////////////////////////////
	
	void ShaderLibrary::add(const std::string& name, const std::shared_ptr<Shader>& shader)
	{
		if (exists(name))
		{
			std::cout << "shader already exists!" << std::endl;
			return;
		}
		m_shaders[name] = shader;
	}

	void ShaderLibrary::add(const std::shared_ptr<Shader>& shader)
	{
		auto& name = shader->get_name();
		add(name, shader);
	}

	std::shared_ptr<Shader> ShaderLibrary::load_impl(const std::string& filepath)
	{
		auto shader = Shader::create(filepath);
		add(shader);
		return shader;
	}

	std::shared_ptr<Shader> ShaderLibrary::load_impl(const std::string& name, const std::string& filepath)
	{
		auto shader = Shader::create(filepath);
		add(name, shader);
		return shader;
	}

	std::shared_ptr<Shader> ShaderLibrary::get_impl(const std::string& name)
	{
		if (!exists(name))
		{
			std::cout << "shader not found!" << std::endl;
			return std::shared_ptr<Shader>();
		}
		return m_shaders[name];
	}

	bool ShaderLibrary::exists(const std::string& name) const
	{
		return m_shaders.find(name) != m_shaders.end();
	}

}