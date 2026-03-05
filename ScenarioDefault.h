#pragma once
#include "Scenario.h"

class ScenarioDefault : public Scenario
{
public:
	ScenarioDefault(Renderer* renderer) {
		this->renderer = renderer;
		name = "Default Scenario";
	}
	virtual void OnLoad() override;
	virtual void OnUpdate(float deltaTime, const InputManager& input) override;
	virtual void OnUnload() override;
};