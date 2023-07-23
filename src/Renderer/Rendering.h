#pragma once
#include "../Core/Timestep.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

namespace Engine {

	class Rendering
	{
	public:
		Rendering();
		~Rendering(){}

		void on_update(Timestep ts);

		void ui_render();

		void on_event();
	private:
		glm::vec3 test;
	};
}