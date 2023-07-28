#include "../pch.h"
#include "VertexArray.h"
#include "../Paltform/OpenGL/OpenGLVertexArray.h"
#include "Renderer.h"

namespace Engine {

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

}