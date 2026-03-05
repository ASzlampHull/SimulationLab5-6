#pragma once
#include "Collider.h"
#include "SphereCollider.h"

class PlaneCollider : public Collider
{
private:
	glm::vec3 normal;
	float distance;

public:
	PlaneCollider(const glm::vec3& normal, float distance, Transformations transformations) : 
		normal(normal), distance(distance), Collider(transformations) {};
	virtual ~PlaneCollider() = default;
	virtual void Update(float timeStep) override { }
	virtual void CalculateCollision(Collider* other, glm::vec3& velocity) override;

	const glm::vec3& GetNormal() const { return normal; }
	float GetDistance() const { return distance; }
};