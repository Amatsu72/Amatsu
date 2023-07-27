#include "../pch.h"
#include "Scene.h"
#include <imgui.h>
#include "RenderCommand.h"

namespace Engine {
	Scene::Scene() :m_camera_controller(16.0f / 9.0f, 0.1f, 100.0f)
	{

	}
	void Scene::on_update(Timestep ts)
	{
		glm::vec4 color(test, 1.0f);
		RenderCommand::set_clear_color(color);
		RenderCommand::clear();
	
	}
	void Scene::ui_render()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(test));
		ImGui::End();
		
	}
	void Scene::on_event(Event& e)
	{
		m_camera_controller.on_event(e);
	}
}