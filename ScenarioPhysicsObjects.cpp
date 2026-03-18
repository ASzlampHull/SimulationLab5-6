#include "ScenarioPhysicsObjects.h"
#include "Renderer.h"
#include "InputManager.h"
#include "Model.h"

void ScenarioPhysicsObjects::OnLoad()
{
	std::cout << "Loading Physics Objects Scenario" << name << std::endl;
	renderer->SetNoTextureModels();
	CreatePhysicsObjects();
}

void ScenarioPhysicsObjects::OnUpdate(float deltaTime, const InputManager& input)
{
	currentTimeStep = renderer->GetPhysicsTimeStep();
	renderer->UpdatePhysicsTime();
	renderer->DrawFrame();
	UpdatePhysicsObjects();
	SendPhysicsObjectsToModels();
}

void ScenarioPhysicsObjects::OnUnload()
{
	std::cout << "Unloading Physics Objects Scenario" << name << std::endl;
}

void ScenarioPhysicsObjects::CreatePhysicsObjects()
{
	renderer->GetResourceManager().GetModels();
	for (const auto& pair : renderer->GetResourceManager().GetModels()) {
		const auto& model = pair.second;
		Transformations transform = model.GetTransformations();
		
		physicsObjects.push_back(PhysicsObject(transform, glm::vec3(0.0f), 1.0f));
	}

	physicsObjects[0].CreateSphereCollider(1.3f);
	physicsObjects[1].CreateSphereCollider(1.3f);
	physicsObjects[2].CreatePlaneCollider(glm::vec3(0.0f, -1.0f, 0.0f), 0.10f);
}

void ScenarioPhysicsObjects::UpdatePhysicsObjects()
{
	glm::vec3 gravityForce = glm::vec3(0.0f, 9.81f, 0.0f);
	for (size_t i = 0; i < physicsObjects.size(); ++i) {
		if (i == 2) { // Only apply to first two spheres.
			gravityForce = glm::vec3(0.0f);
		}
		physicsObjects[i].Update(currentTimeStep, gravityForce);
	}

	// Checks for collisions between objects
	for (size_t i = 0; i < physicsObjects.size(); ++i) {
		Collider* colliderA = nullptr;
		physicsObjects[i].GetCollider(colliderA);
		if (!colliderA) continue;

		for (size_t j = i + 1; j < physicsObjects.size(); ++j) {
			Collider* colliderB = nullptr;
			physicsObjects[j].GetCollider(colliderB);
			if (!colliderB) continue;

			// Update collision for both objects if needed
			physicsObjects[i].UpdateCollision(colliderB); 
			physicsObjects[j].UpdateCollision(colliderA);
		}
	}

	for (auto& physicsObject : physicsObjects) {
		physicsObject.UpdateTransformations(currentTimeStep);
	}
}

void ScenarioPhysicsObjects::SendPhysicsObjectsToModels()
{
	renderer->GetResourceManager().GetModels();
	int i = 0;
	for (auto& pair : renderer->GetResourceManager().GetModels()) {
		auto& model = pair.second;
		Transformations transform;
		physicsObjects[i].GetTransformations(transform);
		model.SetTransformations(transform);
		i++;
	}
}
 

