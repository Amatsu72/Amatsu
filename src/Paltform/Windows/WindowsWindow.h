#pragma once
#include "../../Core/Window.h"
#include "../OpenGL/OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Engine {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		~WindowsWindow();
		void on_update() override;

		inline unsigned int get_width() const override { return m_data.Width; }
		inline unsigned int get_height() const override { return m_data.Height; }

		inline void set_event_callback(const EventCallbackFn& callback) override
		{
			m_data.EventCallback = callback;
		}
		void set_VSync(bool enable) override;
		bool is_VSync()const override;

		inline virtual void* get_native_window() const override { return m_window; }

	private:
		void init(const WindowProps& props);
		void shutdown();

		GLFWwindow* m_window;
		GraphicsContext* m_context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			EventCallbackFn EventCallback;
		};
		WindowData m_data;

		bool m_msaa = false;
	};

}