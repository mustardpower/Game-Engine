#include "Unit.h"

Unit::Unit(UNIT_TYPE unit_type, std::map<std::string, double> unitMap, std::string default_unit)
{
	current = default_unit;
	name = unit_type;
	unitsMap = unitMap;
};

std::string Unit::getCurrent()
{
	return current;
}

double Unit::convertToCurrent(double value, std::string unit)
{
	double value_value = unitsMap.at(unit);
	std::string currentUnit = getCurrent();
	double current_value = unitsMap.at(currentUnit);
	return value * (current_value / value_value);
}