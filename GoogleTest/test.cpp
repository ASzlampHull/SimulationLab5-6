#include "pch.h"
#include "../PhysicsLibrary/SphereToSphere.h"
#include "../PhysicsLibrary/LinePoint.h"
#include "../PhysicsLibrary/SphereLine.h"
#include "../PhysicsLibrary/PointToPlane.h"
#include "../PhysicsLibrary/SpherePlane.h"
#include "../PhysicsLibrary/RotateSphere.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

TEST(TestCaseName, TestName) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

#pragma region Sphere-Sphere Collision Tests

TEST(SphereSphereCollision, NoIntersectionCentreAtOrigin) {
	SphereToSphere sphereA(glm::vec3(0, 0, 0), 1);
	SphereToSphere sphereB(glm::vec3(5, 0, 0), 1);

	EXPECT_FALSE(sphereA.Intersects(sphereB));
}

TEST(SphereSphereCollision, NoIntersectionOffsetOrigin) {
	SphereToSphere sphereA(glm::vec3(3, 3, 3), 2);
	SphereToSphere sphereB(glm::vec3(10, 10, 10), 2);

	EXPECT_FALSE(sphereA.Intersects(sphereB));
}

TEST(SphereSphereCollision, IntersectionCentreAtOrigin) {
	SphereToSphere sphereA(glm::vec3(0, 0, 0), 2);
	SphereToSphere sphereB(glm::vec3(2, 0, 0), 2);

	EXPECT_TRUE(sphereA.Intersects(sphereB));
}

TEST(SphereSphereCollision, IntersectionOffsetOrigin) {
	SphereToSphere sphereA(glm::vec3(5, 5, 5), 3);
	SphereToSphere sphereB(glm::vec3(8, 5, 5), 3);

	EXPECT_TRUE(sphereA.Intersects(sphereB));
}

TEST(SphereSphereCollision, ContainedCentreAtOrigin) {
	SphereToSphere sphereA(glm::vec3(0, 0, 0), 3);
	SphereToSphere sphereB(glm::vec3(1, 0, 0), 1);

	EXPECT_TRUE(sphereA.Intersects(sphereB));
}

TEST(SphereSphereCollision, ContainedOffsetOrigin) {
	SphereToSphere sphereA(glm::vec3(6, 6, 6), 5);
	SphereToSphere sphereB(glm::vec3(7, 6, 6), 2);

	EXPECT_TRUE(sphereA.Intersects(sphereB));
}

#pragma endregion

#pragma region Closest Distance from a Point to a Line

TEST(ClosestDistanceToLine, ClosePointOnLine) {
	LinePoint linePoint(glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), glm::vec3(2, 3, 4));
	EXPECT_FLOAT_EQ(linePoint.ClosetDistanceToLine(), 1.41f);
}

TEST(ClosestDistanceToLine, GenIsOnLine) {
	LinePoint linePoint(glm::vec3(1, 2, 3), glm::vec3(0, 0, 0), glm::vec3(3, 6, 9));
	EXPECT_FLOAT_EQ(linePoint.ClosetDistanceToLine(), 0.0f);
}

TEST(ClosestDistanceToLine, VertLineCase) {
	LinePoint linePoint(glm::vec3(0, 0, 1), glm::vec3(2, 2, 0), glm::vec3(4, 5, 3));
	EXPECT_FLOAT_EQ(linePoint.ClosetDistanceToLine(), 3.61f);
}

TEST(ClosestDistanceToLine, HoriLineCase) {
	LinePoint linePoint(glm::vec3(1, 0, 0), glm::vec3(0, 0, 0), glm::vec3(3, 4, 5));
	EXPECT_FLOAT_EQ(linePoint.ClosetDistanceToLine(), 6.40f);
}

TEST(ClosestDistanceToLine, DiagLineCase) {
	LinePoint linePoint(glm::vec3(1, -1, 1), glm::vec3(1, 1, 1), glm::vec3(2, 5, 3));
	EXPECT_FLOAT_EQ(linePoint.ClosetDistanceToLine(), 4.55f);
}

#pragma endregion

#pragma region Sphere Line Intersection Test

TEST(SphereLineIntersection, NoIntersection) {
	SphereLine sphereLine(glm::vec3(5, 5, 5), glm::vec3(1, 0, 0), glm::vec3(0, 0, 0), 3);
	EXPECT_FALSE(sphereLine.DoesLineIntersectSphere());
}

TEST(SphereLineIntersection, PassThroughAtCentre) {
	SphereLine sphereLine(glm::vec3(10, 0, 0), glm::vec3(-1, 0, 0), glm::vec3(10, 0, 0), 5);
	EXPECT_TRUE(sphereLine.DoesLineIntersectSphere());
}

TEST(SphereLineIntersection, PassThroughInsideSphere) {
	SphereLine sphereLine(glm::vec3(3, 2, 2), glm::vec3(1, 0, 0), glm::vec3(2, 2, 2), 5);
	EXPECT_TRUE(sphereLine.DoesLineIntersectSphere());
}

TEST(SphereLineIntersection, PassThroughCentreSphere) {
	SphereLine sphereLine(glm::vec3(-5, 0, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, 0), 3);
	EXPECT_TRUE(sphereLine.DoesLineIntersectSphere());
}

#pragma endregion

#pragma region Closest Distance from a Point to a Plane

TEST(ClosestDistanceToPlane, PointAbovePlane) {
	PointToPlane pointToPlane(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(2, 3, 5));
	EXPECT_FLOAT_EQ(pointToPlane.ClosetDistanceToPlane(), 5.0f);
}

TEST(ClosestDistanceToPlane, PointBelowPlane) {
	PointToPlane pointToPlane(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(2, 3, -4));
	EXPECT_FLOAT_EQ(pointToPlane.ClosetDistanceToPlane(), 4.0f);
}

TEST(ClosestDistanceToPlane, PointOnPlane) {
	glm::vec3 planeNormal = glm::vec3(1, 1, 1);
	planeNormal *= (1.0f / std::sqrt(3.0f));
	PointToPlane pointToPlane(glm::vec3(1, 1, 1), planeNormal, glm::vec3(0, 2, 1));
	EXPECT_FLOAT_EQ(pointToPlane.ClosetDistanceToPlane(), 0.0f);
}

TEST(ClosestDistanceToPlane, PointCloseToPlane) {
	glm::vec3 planeNormal = glm::vec3(1, 1, 0);
	planeNormal *= (1.0f / std::sqrt(2.0f));
	PointToPlane pointToPlane(glm::vec3(0, 0, 0), planeNormal, glm::vec3(1, 1, 1));
	EXPECT_FLOAT_EQ(pointToPlane.ClosetDistanceToPlane(), 1.41f);
}

TEST(ClosestDistanceToPlane, PointNegativeCoordinates) {
	glm::vec3 planeNormal = glm::vec3(1, 1, 1);
	planeNormal *= (1.0f / std::sqrt(3.0f));
	PointToPlane pointToPlane(glm::vec3(-2, -2, -2), planeNormal, glm::vec3(-1, -1, -1));
	EXPECT_FLOAT_EQ(pointToPlane.ClosetDistanceToPlane(), 1.73f);
}

TEST(ClosestDistanceToPlane, PointAlongNormals) {
	glm::vec3 planeNormal = glm::vec3(1, 1, 0);
	planeNormal *= (1.0f / std::sqrt(2.0f));
	PointToPlane pointToPlane(glm::vec3(0, 0, 0), planeNormal, glm::vec3(1, 1, 0));
	EXPECT_FLOAT_EQ(pointToPlane.ClosetDistanceToPlane(), 1.41f);
}

TEST(ClosestDistanceToPlane, PointRandomPlane) {
	glm::vec3 planeNormal = glm::vec3(1, -1, 0);
	planeNormal *= (1.0f / std::sqrt(2.0f));
	PointToPlane pointToPlane(glm::vec3(0, 0, 0), planeNormal, glm::vec3(1, 2, 3));
	EXPECT_FLOAT_EQ(pointToPlane.ClosetDistanceToPlane(), 0.71f);
}

#pragma endregion

#pragma region Sphere to Plane Collision

TEST(SpherePlaneCollision, NoIntersection) {
	SpherePlane spherePlane(glm::vec3(0, 0, 5), glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), 2);
	EXPECT_FALSE(spherePlane.DoesClosetPointIntersectSphere());
}

TEST(SpherePlaneCollision, TouchingPlane) {
	SpherePlane spherePlane(glm::vec3(0, 0, 2), glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), 2);
	EXPECT_TRUE(spherePlane.DoesClosetPointIntersectSphere());
}

TEST(SpherePlaneCollision, IntersectingPlane) {
	SpherePlane spherePlane(glm::vec3(0, 0, 1), glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), 2);
	EXPECT_TRUE(spherePlane.DoesClosetPointIntersectSphere());
}

TEST(SpherePlaneCollision, ContainedInPlane) {
	SpherePlane spherePlane(glm::vec3(0, 0, 0), glm::vec3(0, 0, 1), glm::vec3(0, 0, 0), 2);
	EXPECT_TRUE(spherePlane.DoesClosetPointIntersectSphere());
}

#pragma endregion

#pragma region Rotate Sphere Tests

constexpr float EPSILON = 0.4f;

TEST(RotateSphereTest, Rotate90DegreesX_ApplyToque) {
	float mass = 1.0f;
	float radius = 1.0f;
	glm::vec3 position(0.0f);
	glm::vec3 velocity(0.0f);
	glm::quat orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	glm::vec3 angularVelocity(0.0f);

	RotateSphere sphere(mass, radius, position, velocity, orientation, angularVelocity);

	float angle = glm::half_pi<float>();
	glm::vec3 torque(1.0f, 0.0f, 0.0f);
	float deltaTime = angle;

	sphere.ApplyToque(torque, deltaTime);

	glm::quat expectedOrientation = glm::angleAxis(angle, glm::vec3(1, 0, 0));
	glm::quat actualOrientation = sphere.GetOrientation();

    float dot = glm::dot(expectedOrientation, actualOrientation);
    EXPECT_NEAR(std::abs(dot), 1.0f, EPSILON);
}

TEST(RotateSphereTest, Rotate180DegreesX_ApplyToque) {
    float mass = 1.0f;
    float radius = 1.0f;
    glm::vec3 position(0.0f);
    glm::vec3 velocity(0.0f);
    glm::quat orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    glm::vec3 angularVelocity(0.0f);

    RotateSphere sphere(mass, radius, position, velocity, orientation, angularVelocity);

    float angle = glm::pi<float>();
    glm::vec3 torque(1.0f, 0.0f, 0.0f);
    float deltaTime = angle;

    sphere.ApplyToque(torque, deltaTime);

    glm::quat expectedOrientation = glm::angleAxis(angle, glm::vec3(1, 0, 0));
    glm::quat actualOrientation = sphere.GetOrientation();

    float dot = glm::dot(expectedOrientation, actualOrientation);
    EXPECT_NEAR(std::abs(dot), 1.0f, EPSILON);
}

TEST(RotateSphereTest, Rotate270DegreesX_ApplyToque) {
    float mass = 1.0f;
    float radius = 1.0f;
    glm::vec3 position(0.0f);
    glm::vec3 velocity(0.0f);
    glm::quat orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    glm::vec3 angularVelocity(0.0f);

    RotateSphere sphere(mass, radius, position, velocity, orientation, angularVelocity);

    float angle = 3.0f * glm::half_pi<float>();
    glm::vec3 torque(1.0f, 0.0f, 0.0f);
    float deltaTime = angle;

    sphere.ApplyToque(torque, deltaTime);

    glm::quat expectedOrientation = glm::angleAxis(angle, glm::vec3(1, 0, 0));
    glm::quat actualOrientation = sphere.GetOrientation();

    float dot = glm::dot(expectedOrientation, actualOrientation);
    EXPECT_NEAR(std::abs(dot), 1.0f, EPSILON);
}

TEST(RotateSphereTest, Rotate360DegreesX_ApplyToque) {
    float mass = 1.0f;
    float radius = 1.0f;
    glm::vec3 position(0.0f);
    glm::vec3 velocity(0.0f);
    glm::quat orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    glm::vec3 angularVelocity(0.0f);

    RotateSphere sphere(mass, radius, position, velocity, orientation, angularVelocity);

    float angle = glm::two_pi<float>();
    glm::vec3 torque(1.0f, 0.0f, 0.0f);
    float deltaTime = angle;

    sphere.ApplyToque(torque, deltaTime);

    glm::quat expectedOrientation = glm::angleAxis(angle, glm::vec3(1, 0, 0));
    glm::quat actualOrientation = sphere.GetOrientation();

    float dot = glm::dot(expectedOrientation, actualOrientation);
    EXPECT_NEAR(std::abs(dot), 1.0f, EPSILON);
}

// Y-axis rotations
TEST(RotateSphereTest, Rotate90DegreesY_ApplyToque) {
    float mass = 1.0f;
    float radius = 1.0f;
    glm::vec3 position(0.0f);
    glm::vec3 velocity(0.0f);
    glm::quat orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    glm::vec3 angularVelocity(0.0f);

    RotateSphere sphere(mass, radius, position, velocity, orientation, angularVelocity);

    float angle = glm::half_pi<float>();
    glm::vec3 torque(0.0f, 1.0f, 0.0f);
    float deltaTime = angle;

    sphere.ApplyToque(torque, deltaTime);

    glm::quat expectedOrientation = glm::angleAxis(angle, glm::vec3(0, 1, 0));
    glm::quat actualOrientation = sphere.GetOrientation();

    float dot = glm::dot(expectedOrientation, actualOrientation);
    EXPECT_NEAR(std::abs(dot), 1.0f, EPSILON);
}

TEST(RotateSphereTest, Rotate180DegreesY_ApplyToque) {
    float mass = 1.0f;
    float radius = 1.0f;
    glm::vec3 position(0.0f);
    glm::vec3 velocity(0.0f);
    glm::quat orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    glm::vec3 angularVelocity(0.0f);

    RotateSphere sphere(mass, radius, position, velocity, orientation, angularVelocity);

    float angle = glm::pi<float>();
    glm::vec3 torque(0.0f, 1.0f, 0.0f);
    float deltaTime = angle;

    sphere.ApplyToque(torque, deltaTime);

    glm::quat expectedOrientation = glm::angleAxis(angle, glm::vec3(0, 1, 0));
    glm::quat actualOrientation = sphere.GetOrientation();

    float dot = glm::dot(expectedOrientation, actualOrientation);
    EXPECT_NEAR(std::abs(dot), 1.0f, EPSILON);
}

TEST(RotateSphereTest, Rotate270DegreesY_ApplyToque) {
    float mass = 1.0f;
    float radius = 1.0f;
    glm::vec3 position(0.0f);
    glm::vec3 velocity(0.0f);
    glm::quat orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    glm::vec3 angularVelocity(0.0f);

    RotateSphere sphere(mass, radius, position, velocity, orientation, angularVelocity);

    float angle = 3.0f * glm::half_pi<float>();
    glm::vec3 torque(0.0f, 1.0f, 0.0f);
    float deltaTime = angle;

    sphere.ApplyToque(torque, deltaTime);

    glm::quat expectedOrientation = glm::angleAxis(angle, glm::vec3(0, 1, 0));
    glm::quat actualOrientation = sphere.GetOrientation();

    float dot = glm::dot(expectedOrientation, actualOrientation);
    EXPECT_NEAR(std::abs(dot), 1.0f, EPSILON);
}

TEST(RotateSphereTest, Rotate360DegreesY_ApplyToque) {
    float mass = 1.0f;
    float radius = 1.0f;
    glm::vec3 position(0.0f);
    glm::vec3 velocity(0.0f);
    glm::quat orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    glm::vec3 angularVelocity(0.0f);

    RotateSphere sphere(mass, radius, position, velocity, orientation, angularVelocity);

    float angle = glm::two_pi<float>();
    glm::vec3 torque(0.0f, 1.0f, 0.0f);
    float deltaTime = angle;

    sphere.ApplyToque(torque, deltaTime);

    glm::quat expectedOrientation = glm::angleAxis(angle, glm::vec3(0, 1, 0));
    glm::quat actualOrientation = sphere.GetOrientation();

    float dot = glm::dot(expectedOrientation, actualOrientation);
    EXPECT_NEAR(std::abs(dot), 1.0f, EPSILON);
}

// Z-axis rotations
TEST(RotateSphereTest, Rotate90DegreesZ_ApplyToque) {
    float mass = 1.0f;
    float radius = 1.0f;
    glm::vec3 position(0.0f);
    glm::vec3 velocity(0.0f);
    glm::quat orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    glm::vec3 angularVelocity(0.0f);

    RotateSphere sphere(mass, radius, position, velocity, orientation, angularVelocity);

    float angle = glm::half_pi<float>();
    glm::vec3 torque(0.0f, 0.0f, 1.0f);
    float deltaTime = angle;

    sphere.ApplyToque(torque, deltaTime);

    glm::quat expectedOrientation = glm::angleAxis(angle, glm::vec3(0, 0, 1));
    glm::quat actualOrientation = sphere.GetOrientation();

    float dot = glm::dot(expectedOrientation, actualOrientation);
    EXPECT_NEAR(std::abs(dot), 1.0f, EPSILON);
}

TEST(RotateSphereTest, Rotate180DegreesZ_ApplyToque) {
    float mass = 1.0f;
    float radius = 1.0f;
    glm::vec3 position(0.0f);
    glm::vec3 velocity(0.0f);
    glm::quat orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    glm::vec3 angularVelocity(0.0f);

    RotateSphere sphere(mass, radius, position, velocity, orientation, angularVelocity);

    float angle = glm::pi<float>();
    glm::vec3 torque(0.0f, 0.0f, 1.0f);
    float deltaTime = angle;

    sphere.ApplyToque(torque, deltaTime);

    glm::quat expectedOrientation = glm::angleAxis(angle, glm::vec3(0, 0, 1));
    glm::quat actualOrientation = sphere.GetOrientation();

    float dot = glm::dot(expectedOrientation, actualOrientation);
    EXPECT_NEAR(std::abs(dot), 1.0f, EPSILON);
}

TEST(RotateSphereTest, Rotate270DegreesZ_ApplyToque) {
    float mass = 1.0f;
    float radius = 1.0f;
    glm::vec3 position(0.0f);
    glm::vec3 velocity(0.0f);
    glm::quat orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    glm::vec3 angularVelocity(0.0f);

    RotateSphere sphere(mass, radius, position, velocity, orientation, angularVelocity);

    float angle = 3.0f * glm::half_pi<float>();
    glm::vec3 torque(0.0f, 0.0f, 1.0f);
    float deltaTime = angle;

    sphere.ApplyToque(torque, deltaTime);

    glm::quat expectedOrientation = glm::angleAxis(angle, glm::vec3(0, 0, 1));
    glm::quat actualOrientation = sphere.GetOrientation();

    float dot = glm::dot(expectedOrientation, actualOrientation);
    EXPECT_NEAR(std::abs(dot), 1.0f, EPSILON);
}

TEST(RotateSphereTest, Rotate360DegreesZ_ApplyToque) {
    float mass = 1.0f;
    float radius = 1.0f;
    glm::vec3 position(0.0f);
    glm::vec3 velocity(0.0f);
    glm::quat orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    glm::vec3 angularVelocity(0.0f);

    RotateSphere sphere(mass, radius, position, velocity, orientation, angularVelocity);

    float angle = glm::two_pi<float>();
    glm::vec3 torque(0.0f, 0.0f, 1.0f);
    float deltaTime = angle;

    sphere.ApplyToque(torque, deltaTime);

    glm::quat expectedOrientation = glm::angleAxis(angle, glm::vec3(0, 0, 1));
    glm::quat actualOrientation = sphere.GetOrientation();

    float dot = glm::dot(expectedOrientation, actualOrientation);
    EXPECT_NEAR(std::abs(dot), 1.0f, EPSILON);
}
#pragma endregion