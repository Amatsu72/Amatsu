#include "../../pch.h"
#include "WindowsWindow.h"
#include "../../Event/ApplicationEvent.h"
#include "../../Event/KeyEvent.h"
#include "../../Event/MouseEvent.h"

namespace Engine {

	static uint8_t s_GLFWWindowCount = 0;

	std::unique_ptr<Window> Window::create(const WindowProps& props)
	{
		return std::make_unique<WindowsWindow>(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		shutdown();
	}

	void WindowsWindow::on_update()
	{
		glfwPollEvents();
		m_context->swap_buffers();
	}

	void WindowsWindow::set_VSync(bool enable)
	{
		if (enable)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_data.VSync = enable;
	}

	bool WindowsWindow::is_VSync() const
	{
		return m_data.VSync;
	}

	void WindowsWindow::init(const WindowProps& props)
	{
		m_data.Title = props.Title;
		m_data.Height = props.Height;
		m_data.Width = props.Width;

		std::cout << "window create:" << props.Title << "\t" << props.Height << "," << props.Width << std::endl;

		if (s_GLFWWindowCount == 0)
		{
			int success = glfwInit();
			if (!success)
				std::cout << "Could not intialized GLFW!" << std::endl;
		}

		if (m_msaa)
			glfwWindowHint(GLFW_SAMPLES, 4);

		m_window = glfwCreateWindow((int)props.Width, (int)props.Height, m_data.Title.c_str(), nullptr, nullptr);
		s_GLFWWindowCount++;

		m_context = new OpenGLContext(m_window);
		m_context->init();

		glfwSetWindowUserPointer(m_window, &m_data);
		set_VSync(true);

		//Set GLFW callbacks
		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;
				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});
		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});
		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event((KeyCode)key, 0);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event((KeyCode)key);
						data.EventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						KeyPressedEvent event((KeyCode)key, 1);
						data.EventCallback(event);
						break;
					}
				}
			});
		glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				KeyTypedEvent event((KeyCode)keycode);
				data.EventCallback(event);
			});
		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event((MouseButton)button);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event((MouseButton)button);
						data.EventCallback(event);
						break;
					}
				}
			});
		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});
		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});
	}

	void WindowsWindow::shutdown()
	{
		glfwDestroyWindow(m_window);
		--s_GLFWWindowCount;
		if (s_GLFWWindowCount == 0)
		{
			glfwTerminate();
		}
	}

}