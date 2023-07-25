#pragma once
#include "Window.h"
#include "Timestep.h"
#include "../Event/ApplicationEvent.h"
#include "../Renderer/Scene.h"
#include "../UI/UI.h"

namespace Engine {

	class Application
	{
	public:
		Application();
		~Application();

		void run();
		void on_event(Event& event);

		inline static Application& get() { return *s_instance; }
		inline Window& get_window() { return *m_window; }

	private:
		bool on_window_close(WindowCloseEvent& e);
		bool on_window_resize(WindowResizeEvent& e);

		bool m_running = true;
		bool m_minimized = false;
		float m_lastFrameTime = 0.0f;
		std::unique_ptr<Window> m_window;
		Scene m_rendering;
		std::unique_ptr<UI> m_ui;
		
		static Application* s_instance;
	};

	Application* create_application();
}