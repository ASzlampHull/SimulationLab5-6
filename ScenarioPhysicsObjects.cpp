#include "ScenarioPhysicsObjects.h"
#include "Renderer.h"
#include "InputManager.h"
#include "Model.h"

void ScenarioPhysicsObjects::OnLoad()
{
	std::cout << "Loading Physics Objects Scenario" << name << std::endl;
	renderer->SetNoTextureModels();
	CreatePhysicsObjects();

	/*std::vector<std::string> sjgFilePaths;
	std::vector<Transformations> transformations;
	sjgFilePaths.push_back("models/PhysicsObjects/sphere.sjg");
	Transformations transform = { glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f) };
	transformations.push_back(transform);
	sjgFilePaths.push_back("models/PhysicsObjects/plane.sjg");
	transform = { glm::vec3(5.0f, 2.0f, 0.0f), glm::vec3(90.0f, 0.0f, 0.0f), glm::vec3(1.0f) };
	transformations.push_back(transform);
	renderer->GetResourceManager().CreateSJGModels(sjgFilePaths, transformations);
	renderer->GetResourceManager().CreateVertexIndexBuffers(renderer->GetCoreVulkanPtr(), renderer->GetCommandPoolVulkanPtr());
	renderer->GetResourceManager().CreateTextures(renderer->GetCoreVulkanPtr(), renderer->GetCommandPoolVulkanPtr(), renderer->GetPipelineVulkanPtr(), renderer->GetUniformBufferObject());
	*/
}

void ScenarioPhysicsObjects::OnUpdate(float deltaTime, const InputManager& input)
{
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

	physicsObjects[0].CreateSphereCollider(1.0f);
	physicsObjects[1].CreateSphereCollider(1.0f);
	physicsObjects[2].CreatePlaneCollider(glm::vec3(0.0f, -1.0f, 0.0f), 0.10f);
}

void ScenarioPhysicsObjects::UpdatePhysicsObjects()
{
	glm::vec3 gravityForce = glm::vec3(0.0f, 9.81f, 0.0f);
	int i = 0;
	for (auto& physicsObject : physicsObjects) {
		if (i == 2) { // Only apply to first two spheres.
			gravityForce = glm::vec3(0.0f);
		}
		physicsObject.Update(renderer->GetPhysicsTimeStep(), gravityForce);
		i++;
	}

	// Checks for collisions between objects
	for (size_t i = 0; i < physicsObjects.size(); ++i) {
		for (size_t j = i + 1; j < physicsObjects.size(); ++j) {
			Collider* colliderA = nullptr;
			physicsObjects[j].GetCollider(colliderA);
			physicsObjects[i].UpdateCollision(colliderA);
		}
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
 

