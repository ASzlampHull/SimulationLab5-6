#pragma once
#include "Scenario.h"

class ScenarioClearColor : public Scenario
{
public:
	ScenarioClearColor(Renderer* renderer) {
		this->renderer = renderer;
		name = "Clear Color Scenario";
	}
	virtual void OnLoad() override;
	virtual void OnUpdate(float deltaTime, const InputManager& input) override;
	virtual void OnUnload() override;
};