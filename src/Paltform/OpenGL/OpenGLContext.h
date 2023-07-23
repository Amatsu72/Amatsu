#pragma once
#include "../../Renderer/GraphicsContext.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Engine {
	
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* window_handle);

		void init() override;
		void swapBuffers() override;

	private:
		GLFWwindow* m_window_handle;
	};

}