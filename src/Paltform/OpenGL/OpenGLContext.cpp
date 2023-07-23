#include "../../pch.h"
#include "OpenGLContext.h"

namespace Engine {
	OpenGLContext::OpenGLContext(GLFWwindow* window_handle)
		:m_window_handle(window_handle) {}

	void OpenGLContext::init()
	{
		glfwMakeContextCurrent(m_window_handle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (!status)
			std::cout << "Failed to initialize GLAD" << std::endl;	
	}

	void OpenGLContext::swapBuffers()
	{
		glfwSwapBuffers(m_window_handle);
	}
}