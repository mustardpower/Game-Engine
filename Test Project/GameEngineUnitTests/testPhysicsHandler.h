#pragma once

#include "gtest/gtest.h"
#include "TestSettings.h"
#include <PhysicsHandler.h>

TEST(testPhysicsHandler, testLinePlaneCollision)
{
	PhysicsHandler physicsHandler;

	glm::vec3 lineOrigin(0.0,0.0,-30.0);
	glm::vec3 lineDirection(-0.006, 0.075, 0.997);
	glm::vec3 planePoint(0.5, 0.5, -1.0);
	glm::vec3 planeNormal(0.0, 0.0, 1.0);
	glm::vec3 collisionPoint = physicsHandler.linePlaneCollisionPoint(lineOrigin,lineDirection,planePoint,planeNormal);
	EXPECT_EQ(collisionPoint, glm::vec3(-0.174523577, 2.18154478,-1.0));
}
