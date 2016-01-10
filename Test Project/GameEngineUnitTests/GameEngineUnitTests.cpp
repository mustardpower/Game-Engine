// UnitTest_Calc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>

// This header file defines the public API for Google Test.
//It should be included by any test program that uses Google Test.
#include "gtest/gtest.h"
#include <SceneManager.h>

/* TEST(test_case_name, test_name) is a predefined macro.
These are ordinary C++ functions that don't return a value.
In this function, along with any valid C++ statements you want to include,
use the various Google Test assertions to check values.
The test's result is determined by the assertions;
if any assertion in the test fails (either fatally or non-fatally),
or if the test crashes, the entire test fails. Otherwise, it succeeds.
*/

std::string testFileDirectory = "C:\\Users\\paul\\Documents\\GitHub\\Game-Engine\\Test Project\\GameEngineUnitTests\\Test Files";

TEST(testSceneManager, testXMLRead)
{
	SceneManager sceneManager;
	sceneManager.fromXML(testFileDirectory + "\\SceneRendering\\test_cube.xml");
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

int _tmain(int argc, _TCHAR* argv[])
{
	/*The method is initializes the Google framework and must be called before RUN_ALL_TESTS */
	::testing::InitGoogleTest(&argc, argv);

	/*RUN_ALL_TESTS automatically detects and runs all the tests defined using the TEST macro.
	It's must be called only once in the code because multiple calls lead to conflicts and,
	therefore, are not supported.
	*/
	return RUN_ALL_TESTS();
}
