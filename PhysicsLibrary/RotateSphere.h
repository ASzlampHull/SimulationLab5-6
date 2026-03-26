#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>


class RigidBody
{
private:

    float mass = 1.0f;
    glm::vec3 position = glm::vec3(0.0f);
    glm::quat orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

	glm::vec3 velocity = glm::vec3(0.0f);
	glm::vec3 angularAcceleration = glm::vec3(0.0f);
	glm::vec3 angularVelocity = glm::vec3(0.0f);
	glm::vec3 accumulatedTorque = glm::vec3(0.0f);

public:
	RigidBody() = default;
    RigidBody(const RigidBody& other)
        : mass(other.mass),
        position(other.position),
        orientation(other.orientation),
        velocity(other.velocity),
        angularAcceleration(other.angularAcceleration),
        angularVelocity(other.angularVelocity),
        accumulatedTorque(other.accumulatedTorque)
    {
    }
	RigidBody(float mass_, glm::vec3 position_, glm::quat orientation_)
		: mass(mass_), position(position_), orientation(orientation_)
	{
	}

	~RigidBody() = default;

    void ApplyToque(glm::vec3 torque, float deltaTime);
    void AddAngularDisplacement(glm::vec3 angularDisplacement);
    void ApplyAngularVelocity(float deltaTime);
    void AccumulateTorqueAndAngularAcceleration(const glm::vec3& appliedForce, const glm::vec3& leverPoint, float deltaTime);
    void AccumulateTorqueAndAngularAccelerationWithInertia(const glm::vec3& appliedForce, const glm::vec3& leverPoint, float deltaTime, float radius);
    void AccumulateTorqueAndAngularAccelerationWithInertiaTensor(const glm::vec3& appliedForce, const glm::vec3& leverPoint, float deltaTime, float radius, float height);
    
	void UpdatePosition(glm::vec3 newPosition) { position = newPosition; }

    const glm::vec3& GetAngularVelocity() const { return angularVelocity; }
	const glm::vec3& GetAngularAcceleration() const { return angularAcceleration; }
	const glm::quat& GetOrientation() const { return orientation; }
	const glm::vec3& GetAccumulatedTorque() const { return accumulatedTorque; }
};
