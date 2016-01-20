#pragma once
#include "BoundingObject.h"

class AABB : public BoundingObject
{
private:
	glm::vec3 vecMin;	// in local coordinates
	glm::vec3 vecMax;	// in local coordinates
public:
	AABB();
	AABB(glm::vec3 min, glm::vec3 max);

	bool contains(glm::vec3 point);
	bool intersects(AABB* aBoundingBox);
	bool intersects(glm::vec3 origin, glm::vec3 dir);
};