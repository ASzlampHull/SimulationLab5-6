#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

class LinePoint
{
public:
	LinePoint(glm::vec3 dir_, glm::vec3 startPt_, glm::vec3 genPt_) : direction(dir_), startingPoint(startPt_), generalPoint(genPt_) {
		normalizedDirection = glm::normalize(direction);
	}
	~LinePoint() = default;

	float ClosetDistanceToLine();

private:
	glm::vec3 direction;
	glm::vec3 normalizedDirection;
	glm::vec3 startingPoint;
	glm::vec3 generalPoint;
};
