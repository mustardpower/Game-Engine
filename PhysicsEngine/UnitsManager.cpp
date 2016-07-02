#include "UnitsManager.h"

std::vector<Unit> UnitsManager::units = UnitsManager::initializeUnits();

void UnitsManager::addUnit(Unit unit)
{
	units.push_back(unit);
}

std::map<UNIT_TYPE, std::string> UnitsManager::defaultUnits()
{
	std::map<UNIT_TYPE, std::string> default_units;

	default_units.insert(std::pair<UNIT_TYPE, std::string>(UNIT_VELOCITY, "m/s"));

	return default_units;
}

std::vector<Unit> UnitsManager::initializeUnits()
{
	std::vector<Unit> allUnits;
	std::map<std::string, double> velocityMap;
	velocityMap.insert(std::pair<std::string, double>("m/s", 1.0));
	velocityMap.insert(std::pair<std::string, double>("km/s", 0.001));
	velocityMap.insert(std::pair<std::string, double>("kmph", 3.6));
	velocityMap.insert(std::pair<std::string, double>("mph", 2.23694));
	velocityMap.insert(std::pair<std::string, double>("ft/s", 3.2808453346457));
	velocityMap.insert(std::pair<std::string, double>("knot", 1.9438477170141412742));
	std::string default_unit = UnitsManager::defaultUnits().at(UNIT_VELOCITY);
	Unit velocityUnit(UNIT_VELOCITY, velocityMap, default_unit);
	allUnits.push_back(velocityUnit);

	return allUnits;
}



std::string UnitsManager::currentUnit(UNIT_TYPE unit_type)
{
	Unit unit = units.at(unit_type);
	return unit.getCurrent();
}