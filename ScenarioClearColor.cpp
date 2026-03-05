#include "ScenarioClearColor.h"
#include "Renderer.h"
#include "InputManager.h"

void ScenarioClearColor::OnLoad()
{
	std::cout << "Loading Clear Color Scenario" << name << std::endl;
}

void ScenarioClearColor::OnUpdate(float deltaTime, const InputManager& input)
{
	renderer->DrawFrame();
}

void ScenarioClearColor::OnUnload()
{
	std::cout << "Unloading Clear Color Scenario" << name << std::endl;
}
