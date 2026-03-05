#include "pch.h"
#include "PointToPlane.h"

float PointToPlane::ClosetDistanceToPlane()
{
	glm::vec3 pointToPlane = generalPoint - startingPoint;
	float distance = glm::dot(pointToPlane, normalizedPlane);
	float roundedDistance = std::round(std::abs(distance) * 100.0f) / 100.0f;
	return roundedDistance;
}
