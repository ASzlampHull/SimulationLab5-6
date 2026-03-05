#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class SpherePlane
{
private:
	glm::vec3 planePoint;
	glm::vec3 planeNormal;
	glm::vec3 sphereCentre;
	float sphereRadius;

public:
	SpherePlane(glm::vec3 point_, glm::vec3 planeNormal_, glm::vec3 sphereCentre_, float sphereRadius_)
		: planePoint(point_), planeNormal(glm::normalize(planeNormal_)), sphereCentre(sphereCentre_), sphereRadius(sphereRadius_) {
	}
	~SpherePlane() = default;
	bool DoesClosetPointIntersectSphere() const;
};
