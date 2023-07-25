#include "../pch.h"
#include "Scene.h"
#include <imgui.h>

#include <glad/glad.h>

namespace Engine {
	Scene::Scene() :m_camera_controller(16.0f / 9.0f, 0.1f, 100.0f)
	{
	}
	void Scene::on_update(Timestep ts)
	{
		glClearColor(0, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	void Scene::ui_render()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(test));
		ImGui::End();
		
	}
	void Scene::on_event()
	{

	}
}