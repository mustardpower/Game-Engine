#pragma once
#include "glm\glm.hpp"

class BoundingObject
{
public:
	virtual bool contains(glm::vec3 point) const = 0;
};