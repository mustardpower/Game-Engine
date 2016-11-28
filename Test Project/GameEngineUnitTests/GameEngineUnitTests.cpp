// UnitTest_Calc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <string>

// This header file defines the public API for Google Test.
//It should be included by any test program that uses Google Test.
#include "gtest/gtest.h"
#include "testGameEngine.h"
#include "testPhysicsHandler.h"

/* TEST(test_case_name, test_name) is a predefined macro.
These are ordinary C++ functions that don't return a value.
In this function, along with any valid C++ statements you want to include,
use the various Google Test assertions to check values.
The test's result is determined by the assertions;
if any assertion in the test fails (either fatally or non-fatally),
or if the test crashes, the entire test fails. Otherwise, it succeeds.
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
