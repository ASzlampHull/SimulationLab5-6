#include "PhysicsObject.h"
#include "PhysicsLibrary/pch.h"

void PhysicsObject::Update(float timeStep, glm::vec3 force)
{
	ApplyForces(timeStep, force);
}

void PhysicsObject::UpdateCollision(Collider* other) {
	if (collider) {
		collider->CalculateCollision(other, velocity);
		collider->GetTransformations(transformations);
	}
}

void PhysicsObject::UpdateTransformations(float timeStep)
{
	transformations.position += velocity * timeStep;
	transformations.rotation += angularVelocity * timeStep;
	collider->UpdateTransformations(transformations);
}

void PhysicsObject::ApplyForces(float timeStep, glm::vec3 force)
{
	if (isStatic) {
		return; // Static objects do not respond to forces
	}

	//Calculate Acceleration
	glm::vec3 acceleration = force / mass;

	//Calculate Velocity
	velocity += acceleration * timeStep;
}

void PhysicsObject::ApplyAngularForces(float timeStep, glm::vec3 force)
{
	if (isStatic) {
		return; // Static objects do not respond to forces
	}

	angularVelocity = force;

	RotateSphere sphere = RotateSphere(mass, 1.0f, transformations.position, velocity, orientation, angularVelocity);

	sphere.ApplyAngularVelocity(timeStep);
	angularVelocity = sphere.GetAngularVelocity();
	orientation = sphere.GetOrientation();
}

void PhysicsObject::CreateSphereCollider(float radius) {
	collider = std::make_unique<SphereCollider>(radius, transformations);
}

void PhysicsObject::CreatePlaneCollider(const glm::vec3& normal, float distance)
{
	collider = std::make_unique<PlaneCollider>(normal, distance, transformations);
}


