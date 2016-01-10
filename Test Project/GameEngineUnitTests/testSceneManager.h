#pragma once

#include "gtest/gtest.h"
#include "TestSettings.h"
#include <SceneManager.h>
#include <GameEngine.h>

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

/* Test No. 2
TEST(testCalc, MySecondTest)
{
...
}
*/