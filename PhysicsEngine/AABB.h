#pragma once
#include "BoundingObject.h"

//-----------------------------------------------------------------------------
// Name:		AABB
// Variables:	vecMin - the minimum point in 3d space that the box is bounding
//				vecMax - the maximum point in 3d space that the box is bounding
// Desc:		Represents an axis aligned bounding box, note that there is no model matrix
//				as some transformations would cause the box to no longer be axis aligned
//-----------------------------------------------------------------------------
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