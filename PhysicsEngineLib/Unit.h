#pragma once
#include <map>
#include <string>

enum UNIT_TYPE
{
	UNIT_LENGTH,
	UNIT_MASS,
	UNIT_VELOCITY,
	UNIT_TORQUE,
	UNIT_TEMPERATURE
};

class Unit
{
private:
	UNIT_TYPE name;
	std::map<std::string, double> unitsMap;
	std::string current;
public:
	Unit(UNIT_TYPE unit_type, std::map<std::string, double> unitMap, std::string default_unit);
	std::string getCurrent();
	double convertToCurrent(double value, std::string value_unit);
};
