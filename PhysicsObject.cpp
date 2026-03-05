#include "PhysicsObject.h"

void PhysicsObject::Update(float timeStep, glm::vec3 force)
{
	CalculateForces(timeStep, force);
}

void PhysicsObject::UpdateCollision(Collider* other) {
	if (collider) {
		collider->CalculateCollision(other, velocity);
		collider->GetTransformations(transformations);
	}
}

void PhysicsObject::CalculateForces(float timeStep, glm::vec3 force)
{
	//Calculate Acceleration
	glm::vec3 acceleration = force / mass;

	//Calculate Velocity
	velocity += acceleration * timeStep;

	//Calculate Position
	transformations.position += velocity * timeStep;
	collider->UpdateTransformations(transformations);
}

void PhysicsObject::CreateSphereCollider(float radius) {
	collider = std::make_unique<SphereCollider>(radius, transformations);
}

void PhysicsObject::CreatePlaneCollider(const glm::vec3& normal, float distance)
{
	collider = std::make_unique<PlaneCollider>(normal, distance, transformations);
}


