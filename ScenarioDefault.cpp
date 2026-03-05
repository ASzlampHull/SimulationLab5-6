#include "ScenarioDefault.h"
#include "Renderer.h"
#include "InputManager.h"

void ScenarioDefault::OnLoad() {
	std::cout << "Loading Default Scenario" << name << std::endl;
}

void ScenarioDefault::OnUpdate(float deltaTime, const InputManager& input) {
	//DayNightSeasonal& dayNightSeasonal = renderer->GetDayNightSeasonal();
	//ResourceManager& resourceManager = renderer->GetResourceManager();
	//auto& models = resourceManager.GetModels();
	//dayNightSeasonal.Update(deltaTime, input, models.at("sun"), models.at("moon"));

	renderer->DrawFrame();
}

void ScenarioDefault::OnUnload() {
	std::cout << "Unloading Default Scenario" << name << std::endl;
	//renderer->GetResourceManager().ClearModels();
}