#pragma once
#include "Collider.h"
#include "PlaneCollider.h"

class SphereCollider : public Collider
{
private:
	float radius;
public:
	SphereCollider(float radius, Transformations transformations) : radius(radius), Collider(transformations) {};
	virtual ~SphereCollider() = default;
	virtual void Update(float timeStep) override { }
	virtual void CalculateCollision(Collider* other, glm::vec3& velocity) override;
	float GetRadius() const { return radius; }
};
