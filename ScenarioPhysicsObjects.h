#pragma once
#include "Scenario.h"
#include "PhysicsObject.h"
#include "ModelParserDataTypes.h"
#include <vector>

class ScenarioPhysicsObjects : public Scenario
{
private:
	std::vector<PhysicsObject> physicsObjects;
public:
	ScenarioPhysicsObjects(Renderer* renderer) {
		this->renderer = renderer;
		name = "Physics Objects Scenario";
	}
	virtual void OnLoad() override;
	virtual void OnUpdate(float deltaTime, const InputManager& input) override;
	virtual void OnUnload() override;

	void CreatePhysicsObjects();
	void UpdatePhysicsObjects();
	void SendPhysicsObjectsToModels();
};