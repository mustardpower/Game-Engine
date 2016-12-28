#pragma once
#include "Unit.h"
#include <string>
#include <map>
#include <vector>

class UnitsManager
{
private:
	static std::vector<Unit> units;
public:
	UnitsManager();
	static std::vector<Unit> initializeUnits();
	static std::map<UNIT_TYPE, std::string> defaultUnits();
	static void addUnit(Unit unit);
	static std::string currentUnit(UNIT_TYPE aType);
	static double convertToCurrentUnit(double value, std::string value_unit, UNIT_TYPE unit_type);
};
