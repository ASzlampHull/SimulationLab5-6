#include "PhysicsObject.h"

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
	transformations.rotation += glm::eulerAngles(orientation);
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

	rigidBody.UpdatePosition(transformations.position);

	if (dynamic_cast<SphereCollider*>(collider.get()))
	{
		rigidBody.AccumulateTorqueAndAngularAccelerationWithInertia(force, glm::vec3(1.0f, 0.0f, 0.0f), timeStep, dynamic_cast<SphereCollider*>(collider.get())->GetRadius());
	}
	else
		rigidBody.AccumulateTorqueAndAngularAcceleration(force, glm::vec3(1.0f, 0.0f, 0.0f), timeStep);

	angularVelocity = rigidBody.GetAngularVelocity();
	orientation = rigidBody.GetOrientation();
}

void PhysicsObject::CreateSphereCollider(float radius) {
	collider = std::make_unique<SphereCollider>(radius, transformations);
}

void PhysicsObject::CreatePlaneCollider(const glm::vec3& normal, float distance)
{
	collider = std::make_unique<PlaneCollider>(normal, distance, transformations);
}


