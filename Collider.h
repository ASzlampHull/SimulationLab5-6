#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ModelParserDataTypes.h"

class Collider
{
private:

protected:
	Transformations transformations;

public:
	Collider() = default;
	Collider(const Transformations transformations) : transformations(transformations) {};
	virtual ~Collider() = default;
	virtual void Update(float deltaTime) = 0;
	virtual void CalculateCollision(Collider* other, glm::vec3& velocity) = 0;

	void UpdateTransformations(const Transformations& newTransformations) { transformations = newTransformations; }
	void GetTransformations(Transformations& outTransformations) const { outTransformations = transformations; }
};
