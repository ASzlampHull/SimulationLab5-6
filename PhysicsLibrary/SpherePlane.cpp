#include "pch.h"
#include "SpherePlane.h"

bool SpherePlane::DoesClosetPointIntersectSphere() const
{
	glm::vec3 toShere = sphereCentre - planePoint;
	float distanceToPlane = glm::dot(toShere, planeNormal);
	glm::vec3 closestPoint = sphereCentre - distanceToPlane * planeNormal;
	glm::vec3 closetPointToSphere = closestPoint - sphereCentre;

	return glm::length(closetPointToSphere) <= sphereRadius;
}
