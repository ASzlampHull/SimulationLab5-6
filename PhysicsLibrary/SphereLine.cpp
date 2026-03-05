#include "pch.h"
#include "SphereLine.h"

bool SphereLine::DoesLineIntersectSphere() const
{
	glm::vec3 pointToSphere = point - sphereCentre;

	float squaredDirectionLength = glm::dot(direction, direction);
	float pointToSphereDirection = 2.0f * glm::dot(pointToSphere, direction);
	float pointToSphereDistance = glm::dot(pointToSphere, pointToSphere) - sphereRadius * sphereRadius;

	// Quadratic formula for the intersection of a line and a sphere
	// by substituting the line equation into the sphere equation and rearranging, we get:
	float distanceTraveled = pointToSphereDirection * pointToSphereDirection - 4 * squaredDirectionLength * pointToSphereDistance;

	return distanceTraveled >= 0.0f;
}
