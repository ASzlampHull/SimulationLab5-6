#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>


class RotateSphere
{
private:
    float mass;
    float radius;

    glm::vec3 position;
    glm::vec3 velocity;

    glm::quat orientation;
    glm::vec3 angularVelocity;

public:
	RotateSphere(float mass_, float radius_, glm::vec3 position_, glm::vec3 velocity_, glm::quat orientation_, glm::vec3 angularVelocity_)
		: mass(mass_), radius(radius_), position(position_), velocity(velocity_), orientation(orientation_), angularVelocity(angularVelocity_)
	{
	}
	~RotateSphere() = default;

    void ApplyToque(glm::vec3 torque, float deltaTime);
    void AddAngularDisplacement(glm::vec3 angularDisplacement);
    void ApplyAngularVelocity(float deltaTime);
    
    const glm::vec3& GetAngularVelocity() const { return angularVelocity; }
	const glm::quat& GetOrientation() const { return orientation; }
};
