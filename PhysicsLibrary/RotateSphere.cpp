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