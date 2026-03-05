#include "pch.h"
#include "SphereToSphere.h"

bool SphereToSphere::Intersects(const SphereToSphere& other) const
{
	glm::vec3 centreDiff = other.position - this->position;
	float distanceSquared = glm::dot(centreDiff, centreDiff);
	float radiusSum = this->radius + other.radius;
	float radiusSumSquared = radiusSum * radiusSum;
	float radiusDiff = this->radius - other.radius;
	float radiusDiffSquared = radiusDiff * radiusDiff;

	if (distanceSquared > radiusSumSquared)
		return false;
	if (distanceSquared < radiusDiffSquared)
		return true;
	if (distanceSquared == radiusSumSquared)
		return true;
	if (radiusDiffSquared < distanceSquared && distanceSquared < radiusSumSquared)
		return true;
	if (distanceSquared == radiusDiffSquared)
		return true;
	if (distanceSquared == 0.0f && radiusDiffSquared == 0.0f)
		return true;

	return false;
}