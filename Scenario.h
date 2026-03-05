#pragma once
#include <string>
#include <iostream>

class Renderer;
class InputManager;

class Scenario
{
private:

protected:
	std::string name;
	Renderer* renderer;

public:
	virtual ~Scenario() {};

	virtual void OnLoad() = 0;
	virtual void OnUpdate(float deltaTime, const InputManager& input) = 0;
	virtual void OnUnload() = 0;

	std::string GetName() const { return name; }
};