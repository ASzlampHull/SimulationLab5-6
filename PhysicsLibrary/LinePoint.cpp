#include "pch.h"
#include "LinePoint.h"

float LinePoint::ClosetDistanceToLine()
{
	glm::vec3 lineFromStartToGen = generalPoint - startingPoint;
	// Projection of the vector from the starting point to the general point onto the normalized direction of the line
	float projectionLength = glm::dot(lineFromStartToGen, normalizedDirection);
	// The closest point on the line to the general point can be found by adding the projection vector to the starting point
	glm::vec3 projectionPoint = startingPoint + projectionLength * normalizedDirection;
	glm::vec3 lineFromProjectionToGen = generalPoint - projectionPoint;

	float distance = glm::length(lineFromProjectionToGen);
	float roundedDistance = std::round(distance * 100.0f) / 100.0f;
	return roundedDistance;

	return 0.0f;
}
