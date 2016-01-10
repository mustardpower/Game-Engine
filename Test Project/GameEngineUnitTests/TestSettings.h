#pragma once

#include <string>
#include <Windows.h>

class TestSettings
{
private:
public:
	static std::string getApplicationDirectory();
	static std::string getTestFileDirectory();
};
