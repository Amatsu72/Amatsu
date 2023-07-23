#pragma once
#include "../Event/Event.h"

namespace Engine {

	struct WindowProps {
		std::string Title = "Amatsu";
		unsigned int Width = 1600;
		unsigned int Height = 900;
		bool VSync = true;
	};

	class Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void on_update() = 0;
		virtual unsigned int get_width() const = 0;
		virtual unsigned int get_height() const = 0;

		// Window attributes
		virtual void set_event_callback(const EventCallbackFn& callback) = 0;
		virtual void set_VSync(bool enable) = 0;
		virtual bool is_VSync() const = 0;

		virtual void* get_native_window() const = 0;

		static std::unique_ptr<Window> create(const WindowProps& props = WindowProps());
	};
}