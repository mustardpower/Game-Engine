#pragma once

#include "gtest/gtest.h"
#include "TestSettings.h"
#include <GameEngine.h>
#include <AABB.h>

TEST(testGameEngine, testXMLRead)
{
	GameEngine testEngine("Test");
	testEngine.LoadFromFile(TestSettings::getTestFileDirectory() + "\\SceneRendering\\test_cube.xml");
	std::vector<Renderable> objects = testEngine.getObjects();
	EXPECT_EQ(1, objects.size());
	Renderable object = objects.at(0);

	glm::mat4 modelMatrix(1.00000, 0.00000, 0.00000, 0.00000, 0.00000, 1.00000, 0.00000, 0.00000, 0.00000, 0.00000, 1.00000, 0.00000, 0.00000, 0.00000, 0.00000, 1.00000);
	EXPECT_EQ(modelMatrix, object.getModelMatrix());

	glm::vec3 velocity(15.00000, -7.00000, 12.5000);
	EXPECT_EQ(velocity, object.getVelocity());
}

TEST(testGameEngine, testXMLReadFailure)
{
	GameEngine testEngine("Test");
	int res = testEngine.LoadFromFile(TestSettings::getTestFileDirectory() + "\\SceneRendering\\nonexistant.xml");
	EXPECT_NE(res, tinyxml2::XML_SUCCESS);

	std::vector<Renderable> objects = testEngine.getObjects();
	EXPECT_EQ(0, objects.size());
}

TEST(testGameEngine, testRayCollision)
{
	//bounding box 
	glm::vec3 vecMin(-1.0, -1.0, -1.0);
	glm::vec3 vecMax(1.0, 1.0, 1.0);
	AABB boundingBox(vecMin, vecMax);

	// -------------- SIMPLE TEST CASE 1: ray moving along z towards bounding box at the origin ------------------//
	glm::vec3 origin1(0, 0, -30);
	glm::vec3 direction1(0, 0, 1);
	EXPECT_EQ(TRUE, boundingBox.intersects(origin1, direction1));

	// --------------- SIMPLE TEST CASE 2: intersection method considers only touching edge as not a proper collision ------------//
	glm::vec3 origin2(1, 0, -30);
	EXPECT_EQ(FALSE, boundingBox.intersects(origin2, direction1));
	glm::vec3 origin3(0.9999, 0, -30);
	EXPECT_EQ(TRUE, boundingBox.intersects(origin3, direction1));

	// --------------- SIMPLE TEST CASE 3: ray slightly angled ------------//
	glm::vec3 direction2(-0.006397, 0.0750924, 0.997156);
	EXPECT_EQ(FALSE, boundingBox.intersects(origin1, direction2));
}

TEST(testGameEngine, testAABBCollision)
{
	// --------------- SIMPLE TEST CASE 1: two AABBs in the same place ------------//
	glm::vec3 vecMin1(-1.0, -1.0, -1.0);
	glm::vec3 vecMax1(1.0, 1.0, 1.0);
	AABB boundingBox1(vecMin1, vecMax1);

	glm::vec3 vecMin2(-1.0, -1.0, -1.0);
	glm::vec3 vecMax2(1.0, 1.0, 1.0);
	AABB boundingBox2(vecMin2, vecMax2);

	EXPECT_EQ(TRUE, boundingBox1.intersects(boundingBox2));
	EXPECT_EQ(TRUE, boundingBox2.intersects(boundingBox1));

	// --------------- SIMPLE TEST CASE 2: two AABBs in that do not collide ------------//

	glm::vec3 vecMin3(1.5, -1.0, -1.0);
	glm::vec3 vecMax3(2.5, 1.0, 1.0);
	AABB boundingBox3(vecMin3, vecMax3);
	EXPECT_EQ(FALSE, boundingBox1.intersects(boundingBox3));
	EXPECT_EQ(FALSE, boundingBox3.intersects(boundingBox1));
}