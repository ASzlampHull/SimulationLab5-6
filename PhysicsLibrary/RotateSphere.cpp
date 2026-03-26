#include "RotateSphere.h"
#include "pch.h"
#include "RotateSphere.h"

void RigidBody::ApplyToque(glm::vec3 torque, float deltaTime){
    glm::vec3 angularAcceleration = torque / mass;
    glm::vec3 initialAngularVelocity = angularVelocity;
    angularVelocity += angularAcceleration * deltaTime;
    glm::vec3 averageAngularVelocity = 0.5f * (initialAngularVelocity + angularVelocity);
    AddAngularDisplacement(averageAngularVelocity * deltaTime);
}

void RigidBody::AddAngularDisplacement(glm::vec3 angularDisplacement)
{
    float angle = glm::length(angularDisplacement);
    if (angle > 0.0f) {
        glm::vec3 axis = glm::normalize(angularDisplacement);
        glm::quat deltaOrientation = glm::angleAxis(angle, axis);
        orientation = glm::normalize(deltaOrientation * orientation);
    }
}

void RigidBody::ApplyAngularVelocity(float deltaTime) {
    AddAngularDisplacement(angularVelocity * deltaTime);
}

void RigidBody::AccumulateTorqueAndAngularAcceleration(const glm::vec3& appliedForce, const glm::vec3& leverPoint, float deltaTime) {    
    glm::vec3 leverArm = leverPoint - position;    
    glm::vec3 torque = glm::cross(leverArm, appliedForce); // Torque = l x F (right-hand rule)
    accumulatedTorque += torque;
    angularAcceleration = accumulatedTorque / mass;

    glm::vec3 initialAngularVelocity = angularVelocity;
    angularVelocity += angularAcceleration * deltaTime;
    glm::vec3 averageAngularVelocity = 0.5f * (initialAngularVelocity + angularVelocity);
    AddAngularDisplacement(averageAngularVelocity * deltaTime);
}

// Overload that takes radius for inertia calculation (assuming solid sphere)
void RigidBody::AccumulateTorqueAndAngularAccelerationWithInertia(const glm::vec3& appliedForce, const glm::vec3& leverPoint, float deltaTime, float radius)
{
    float inertia = (2.0f / 5.0f) * mass * radius * radius;
    glm::vec3 leverArm = leverPoint - position;
    glm::vec3 torque = glm::cross(leverArm, appliedForce); // Torque = l x F (right-hand rule)
    accumulatedTorque += torque;
    angularAcceleration = accumulatedTorque / inertia;

    glm::vec3 initialAngularVelocity = angularVelocity;
    angularVelocity += angularAcceleration * deltaTime;
    glm::vec3 averageAngularVelocity = 0.5f * (initialAngularVelocity + angularVelocity);
    AddAngularDisplacement(averageAngularVelocity * deltaTime);
}

void RigidBody::AccumulateTorqueAndAngularAccelerationWithInertiaTensor(const glm::vec3& appliedForce, const glm::vec3& leverPoint, float deltaTime, float radius, float height)
{
    // Calculate the principal moments of inertia for a solid cylinder along the Y-axis
    float I_x = (1.0f / 12.0f) * mass * (3.0f * radius * radius + height * height);
    float I_y = 0.5f * mass * radius * radius;
    float I_z = I_x;

    glm::mat3 inertiaTensor = glm::mat3(0.0f);
    inertiaTensor[0][0] = I_x;
    inertiaTensor[1][1] = I_y;
    inertiaTensor[2][2] = I_z;

    glm::vec3 leverArm = leverPoint - position;
    glm::vec3 torque = glm::cross(leverArm, appliedForce);
    accumulatedTorque += torque;

    angularAcceleration = glm::inverse(inertiaTensor) * accumulatedTorque;

    glm::vec3 initialAngularVelocity = angularVelocity;
    angularVelocity += angularAcceleration * deltaTime;
    glm::vec3 averageAngularVelocity = 0.5f * (initialAngularVelocity + angularVelocity);
    AddAngularDisplacement(averageAngularVelocity * deltaTime);
}