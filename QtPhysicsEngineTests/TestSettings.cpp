#include "TestSettings.h"
#include <QDir>

// application directory refers to the test project application
// and not the application being tested
QString TestSettings::getApplicationDirectory()
{
	return QDir::currentPath();
}
QString TestSettings::getTestFileDirectory()
{
	return getApplicationDirectory() + "\\Test Files";
}