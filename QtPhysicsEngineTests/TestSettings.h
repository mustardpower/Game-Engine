#pragma once

#include <QString>

class TestSettings
{
private:
public:
	static QString getApplicationDirectory();
	static QString getTestFileDirectory();
};
