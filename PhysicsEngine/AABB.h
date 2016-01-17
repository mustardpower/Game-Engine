#pragma once
#include "BoundingObject.h"

class AABB : public BoundingObject
{
private:
	glm::vec3 vecMin;	// bottom corner closest to origin
	glm::vec3 vecMax;	// top corner furthest from origin
public:
	AABB() {};
	AABB(glm::vec3 a,glm::vec3 b) { vecMin = a; vecMax = b; }
	bool contains(glm::vec3 point);
	bool intersects(AABB* aBoundingBox);
	bool intersects(glm::vec3 origin, glm::vec3 dir);
};