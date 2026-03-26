#pragma once
#include <memory>
#include "Collider.h"
#include "SphereCollider.h"
#include "PlaneCollider.h"
#include <glm/gtc/quaternion.hpp>
#include "PhysicsLibrary/pch.h"

class PhysicsObject
{
private:
	Transformations transformations;
	glm::vec3 velocity;
	glm::vec3 angularVelocity;
	glm::quat orientation;
	float mass;
	bool isStatic; // Add a flag to indicate if the object is static or dynamic
	std::unique_ptr<Collider> collider; // Use smart pointer
	RigidBody rigidBody;

public:
	PhysicsObject(Transformations transformations, glm::vec3 velocity, glm::vec3 angularVelocity, glm::quat orientation, float mass, bool isStatic = false)
		: transformations(transformations), velocity(velocity), angularVelocity(angularVelocity), orientation(orientation), mass(mass), isStatic(isStatic)
	{
		rigidBody = RigidBody(mass, transformations.position, orientation);
	}

	void Update(float deltaTime, glm::vec3 force);
	void UpdateCollision(Collider* other);
	void UpdateTransformations(float timeStep);
	void ApplyForces(float timeStep, glm::vec3 force);
	void ApplyAngularForces(float timeStep, glm::vec3 force);
	void CreateSphereCollider(float radius);
	void CreatePlaneCollider(const glm::vec3& normal, float distance);

	void GetTransformations(Transformations& outTransformations) const { outTransformations = transformations; }
	void GetCollider(Collider*& outCollider) const { outCollider = collider.get(); }
};