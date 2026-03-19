#include "pch.h"
#include "RotateSphere.h"

void RotateSphere::ApplyToque(glm::vec3 torque, float deltaTime){
    glm::vec3 angularAcceleration = torque / mass;
    glm::vec3 initialAngularVelocity = angularVelocity;
    angularVelocity += angularAcceleration * deltaTime;
    glm::vec3 averageAngularVelocity = 0.5f * (initialAngularVelocity + angularVelocity);
    AddAngularDisplacement(averageAngularVelocity * deltaTime);
}

void RotateSphere::AddAngularDisplacement(glm::vec3 angularDisplacement)
{
    float angle = glm::length(angularDisplacement);
    if (angle > 0.0f) {
        glm::vec3 axis = glm::normalize(angularDisplacement);
        glm::quat deltaOrientation = glm::angleAxis(angle, axis);
        orientation = glm::normalize(deltaOrientation * orientation);
    }
}
