#include "PlaneCollider.h"

void PlaneCollider::CalculateCollision(Collider* other, glm::vec3& velocity)
{
	// Sphere collision
	if (SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(other)) {
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
			float penetrationDepth = sphereRadius - distanceFromPlane;
			sphereTransformations.position += planeNormal * penetrationDepth;
			sphereCollider->UpdateTransformations(sphereTransformations);
		}

		float vDotN = glm::dot(velocity, planeNormal);
		if (vDotN < 0.0f) {
			velocity -= vDotN * planeNormal;
		}
	}
}
