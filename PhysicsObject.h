#pragma once
#include <memory>
#include "Collider.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"

class PhysicsObject
{
private:
	Transformations transformations;
	glm::vec3 velocity;
	float mass;
	std::unique_ptr<Collider> collider; // Use smart pointer

public:
	PhysicsObject(Transformations transformations, glm::vec3 velocity, float mass)
		: transformations(transformations), velocity(velocity), mass(mass) {
	}

	void Update(float deltaTime, glm::vec3 force);
	void UpdateCollision(Collider* other);
	void CalculateForces(float deltaTime, glm::vec3 force);
	void CreateSphereCollider(float radius);
	void CreatePlaneCollider(const glm::vec3& normal, float distance);

	void GetTransformations(Transformations& outTransformations) const { outTransformations = transformations; }
	void GetCollider(Collider*& outCollider) const { outCollider = collider.get(); }
};