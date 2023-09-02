#include "../pch.h"
#include "VertexArray.h"
#include "../Paltform/OpenGL/OpenGLVertexArray.h"
#include "Renderer.h"

namespace Engine {

	VertexArrayLibrary* VertexArrayLibrary::s_instance = new VertexArrayLibrary();

	std::shared_ptr<VertexArray> VertexArray::create()
	{
		switch (Renderer::get_API())
		{
			case RenderAPI::API::None:
				std::cout << "RenderAPI::None is currently nor support!" << std::endl;
				return nullptr;
			case RenderAPI::API::OpenGL:
				return std::make_shared<OpenGLVertexArray>();
		}
		std::cout << "Unkonwn RenderAPI!" << std::endl;
		return nullptr;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////

	void VertexArrayLibrary::add(const std::string& name, const std::shared_ptr<VertexArray>& vertex_array)
	{
		if (exists(name))
		{
			std::cout << "vertex array already exists!" << std::endl;
			return;
		}
		m_vertex_arrays[name] = vertex_array;
	}

	std::shared_ptr<VertexArray> VertexArrayLibrary::load_impl(const std::string& name)
	{
		auto vertex_array = VertexArray::create();
		add(name, vertex_array);
		return vertex_array;
	}

	std::shared_ptr<VertexArray> VertexArrayLibrary::get_impl(const std::string& name)
	{
		if (!exists(name))
		{
			std::cout << "vertex array not found!" << std::endl;
			return std::shared_ptr<VertexArray>();
		}
		return m_vertex_arrays[name];
	}

	bool VertexArrayLibrary::exists(const std::string& name) const
	{
		return m_vertex_arrays.find(name) != m_vertex_arrays.end();
	}

}