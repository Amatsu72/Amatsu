#include "../pch.h"
#include "Application.h"
#include "Macro.h"
#include <GLFW/glfw3.h>
#include "../Renderer/Renderer.h"

namespace Engine {

	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		s_instance = this;
		m_window = std::unique_ptr<Window>(Window::create());
		m_window->set_event_callback(BIND_EVENT_FN(Application::on_event));
			
		Renderer::init();
		m_scene = std::make_unique<Scene>();
		m_ui = std::make_unique<UI>();
		m_ui->init();
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		while (m_running)
		{
			float time = (float)glfwGetTime();
			Timestep timesetp = time - m_lastFrameTime;
			m_lastFrameTime = time;
			if (!m_minimized)
			{
				m_scene->on_update(timesetp);
				m_ui->begin();
				m_scene->ui_render();
				m_ui->end();
			}
			m_window->on_update();
			//std::cout << 1.0/timesetp << std::endl;
		}
	}

	void Application::on_event(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::on_window_close));
		dispatcher.dispatch<WindowResizeEvent>(BIND_EVENT_FN(Application::on_window_resize));
		m_scene->on_event(event);
	}


	bool Application::on_window_close(WindowCloseEvent& e)
	{
		m_running = false;
		return true;
	}

	bool Application::on_window_resize(WindowResizeEvent& e)
	{
		if (e.get_width() == 0 || e.get_height() == 0)
		{
			m_minimized = true;
			return false;
		}
		m_minimized = false;
		Renderer::on_window_resize(e.get_width(), e.get_height());
		return false;
	}

}