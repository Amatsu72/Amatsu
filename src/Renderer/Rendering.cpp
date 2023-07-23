#include "../pch.h"
#include "Rendering.h"
#include <imgui.h>

#include <glad/glad.h>

namespace Engine {
	Rendering::Rendering()
	{
	}
	void Rendering::on_update(Timestep ts)
	{
		glClearColor(0, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void Rendering::ui_render()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(test));
		ImGui::End();
		
	}
	void Rendering::on_event()
	{

	}
}