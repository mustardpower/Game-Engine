#pragma once

#include "gtest/gtest.h"
#include "TestSettings.h"
#include <SceneManager.h>
#include <GameEngine.h>
#include <AABB.h>

TEST(testSceneManager, testXMLRead)
{
	SceneManager sceneManager;
	sceneManager.fromXML(TestSettings::getTestFileDirectory() + "\\SceneRendering\\test_cube.xml");
	std::vector<Renderable> objects = sceneManager.getObjects();
	EXPECT_EQ(1, objects.size());
	Renderable object = objects.at(0);

	glm::mat4 modelMatrix(1.00000, 0.00000, 0.00000, 0.00000, 0.00000, 1.00000, 0.00000, 0.00000, 0.00000, 0.00000, 1.00000, 0.00000, 0.00000, 0.00000, 0.00000, 1.00000);
	EXPECT_EQ(modelMatrix, object.getModelMatrix());

	glm::vec3 velocity(15.00000, -7.00000, 12.5000);
	EXPECT_EQ(velocity, object.getVelocity());
}

TEST(testSceneManager, testXMLReadFailure)
{
	SceneManager sceneManager;
	tinyxml2::XMLError res = sceneManager.fromXML(TestSettings::getTestFileDirectory() + "\\SceneRendering\\nonexistant.xml");
	EXPECT_NE(res, tinyxml2::XML_SUCCESS);

	std::vector<Renderable> objects = sceneManager.getObjects();
	EXPECT_EQ(0, objects.size());
}

TEST(testSceneManager, testRayCollision)
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

TEST(testSceneManager, testViewportToNormalizedDeviceCoordinates)
{
	SceneManager sceneManager;

	int mouseX = 400;
	int mouseY = 600;
	int screen_width = 1024;
	int screen_height = 1020;

	glm::vec3 ndc = sceneManager.viewportToNormalizedDeviceCoordinates(mouseX, mouseY, screen_width, screen_height);
	glm::vec2 viewportCoordinates = sceneManager.normalizedDeviceCoordinatesToViewport(ndc, screen_width, screen_height);
	EXPECT_EQ(viewportCoordinates.x, mouseX);
	EXPECT_EQ(viewportCoordinates.y, mouseY);
}

/* Test No. 3
TEST(testCalc, MySecondTest)
{
...
}
*/