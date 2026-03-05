#include "SphereCollider.h"
#include "PhysicsLibrary/pch.h"

void SphereCollider::CalculateCollision(Collider* other, glm::vec3& velocity)
{
	//Collides with Plane
	if (PlaneCollider* planeCollider = dynamic_cast<PlaneCollider*>(other)) {
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

	//Collides with Sphere
	if (SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(other)) {
		Transformations otherSphereTransformations;
		sphereCollider->GetTransformations(otherSphereTransformations);
		glm::vec3 otherSpherePosition = otherSphereTransformations.position;
		float otherSphereRadius = sphereCollider->GetRadius();
		Transformations sphereTransformations;
		GetTransformations(sphereTransformations);
		glm::vec3 spherePosition = sphereTransformations.position;
		glm::vec3 delta = spherePosition - otherSpherePosition;
		float distance = glm::length(delta);
		float penetrationDepth = radius + otherSphereRadius - distance;

		if (penetrationDepth > 0) {
			glm::vec3 collisionNormal = glm::normalize(delta);
			sphereTransformations.position += collisionNormal * penetrationDepth;
			UpdateTransformations(sphereTransformations);

			float vDotN = glm::dot(velocity, collisionNormal);
			if (vDotN < 0.0f) {
				velocity -= vDotN * collisionNormal;
			}
		}
		/*Transformations sphereTransformations;
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
		}*/
	}
}
