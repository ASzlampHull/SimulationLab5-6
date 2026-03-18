#include "PlaneCollider.h"
#include "PhysicsLibrary/pch.h"

void PlaneCollider::CalculateCollision(Collider* other, glm::vec3& velocity)
{
	other->CalculateCollisionWithPlane(this, velocity);
}

void PlaneCollider::CalculateCollisionWithSphere(SphereCollider* sphereCollider, glm::vec3& velocity)
{
	Transformations planeTransformations;
	GetTransformations(planeTransformations);
	glm::vec3 planeNormal = normal;
	float planeDistance = distance;
	Transformations sphereTransformations;
	sphereCollider->GetTransformations(sphereTransformations);
	glm::vec3 spherePosition = sphereTransformations.position;
	float sphereRadius = sphereCollider->GetRadius();
	float distanceFromPlane = glm::dot(planeNormal, spherePosition) - planeDistance;

	if (distanceFromPlane < sphereRadius) {
		velocity = glm::vec3(0.0f); // Stop the sphere's velocity when it collides with the plane. You can implement a more complex response if desired.
		/*float penetrationDepth = sphereRadius - distanceFromPlane;
		sphereTransformations.position += planeNormal * penetrationDepth;
		sphereCollider->UpdateTransformations(sphereTransformations);*/
	}
}

void PlaneCollider::CalculateCollisionWithPlane(PlaneCollider* planeCollider, glm::vec3& velocity)
{
}
