#include "SphereCollider.h"
#include "PhysicsLibrary/pch.h"

void SphereCollider::CalculateCollision(Collider* other, glm::vec3& velocity)
{
	other->CalculateCollisionWithSphere(this, velocity);
}

void SphereCollider::CalculateCollisionWithSphere(SphereCollider* sphereCollider, glm::vec3& velocity)
{
	Transformations sphereTransformations;
	GetTransformations(sphereTransformations);

	Transformations otherSphereTransformations;
	sphereCollider->GetTransformations(otherSphereTransformations);

	SphereToSphere sphereA(sphereTransformations.position, radius);
	SphereToSphere sphereB(otherSphereTransformations.position, sphereCollider->GetRadius());

	if (sphereA.Intersects(sphereB)) {
		glm::vec3 delta = sphereTransformations.position - otherSphereTransformations.position;
		float distance = glm::length(delta);
		float penetrationDepth = radius + sphereCollider->GetRadius() - distance;
		if (penetrationDepth > 0) {
			glm::vec3 collisionNormal = glm::normalize(delta);
			sphereTransformations.position += collisionNormal * penetrationDepth;
			UpdateTransformations(sphereTransformations);
			float vDotN = glm::dot(velocity, collisionNormal);
			if (vDotN < 0.0f) {
				velocity -= vDotN * collisionNormal;
			}
		}
	}
}

void SphereCollider::CalculateCollisionWithPlane(PlaneCollider* planeCollider, glm::vec3& velocity)
{
	Transformations planeTransformations;
	planeCollider->GetTransformations(planeTransformations);

	glm::vec3 planeNormal = planeCollider->GetNormal();
	float planeDistance = planeCollider->GetDistance();
	Transformations sphereTransformations;
	GetTransformations(sphereTransformations);
	glm::vec3 spherePosition = sphereTransformations.position;
	float distanceFromPlane = glm::dot(planeNormal, spherePosition) - planeDistance;

	if (distanceFromPlane < radius) {
		float penetrationDepth = radius - distanceFromPlane;
		sphereTransformations.position += planeNormal * penetrationDepth;
		UpdateTransformations(sphereTransformations);

		float vDotN = glm::dot(velocity, planeNormal);
		if (vDotN < 0.0f) {
			velocity -= vDotN * planeNormal;
		}
	}
}
