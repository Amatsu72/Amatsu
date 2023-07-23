#include "pch.h"
#include "engine.h"

//extern Engine::Application* Engine::create_application();

int main()
{
	auto app = Engine::create_application();
	app->run();
	delete app;
	
}

Engine::Application* Engine::create_application()
{
	return new Engine::Application();
}
