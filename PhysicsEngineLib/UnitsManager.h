#pragma once

#include <string>
#include <map>
#include <vector>

enum UNIT_TYPE
{
	UNIT_LENGTH,
	UNIT_MASS,
	UNIT_VELOCITY,
	UNIT_TORQUE,
	UNIT_TEMPERATURE
};

struct Unit
{
	UNIT_TYPE name;
	std::map<std::string, double> unitsMap;
	std::string current;

	Unit(UNIT_TYPE unit_type, std::map<std::string, double> unitMap, std::string default_unit)
	{
		current = default_unit;
		name = unit_type;
		unitsMap = unitMap;
	};

	std::string getCurrent()
	{
		return current;
	}
};

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
};
