#include "stdafx.h"
#include "TestSettings.h"

// application directory refers to the test project application
// and not the application being tested
std::string TestSettings::getApplicationDirectory()
{
	TCHAR pathBuffer[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, pathBuffer);
	return std::string(pathBuffer);
}
std::string TestSettings::getTestFileDirectory()
{
	return getApplicationDirectory() + "\\Test Files";
}