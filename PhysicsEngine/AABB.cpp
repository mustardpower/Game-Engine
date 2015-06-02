#include "AABB.h"

bool AABB::contains(glm::vec3 point)
{
	// check point x,y,z values are within the axis-aligned bounding box - return true if they are, false if not
	if((point.x > vecMin.x && point.x < vecMax.x)
		&&(point.y > vecMin.y && point.y < vecMax.y)
		&&(point.z > vecMin.z && point.z < vecMax.z))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool AABB::intersects(AABB* aBoundingBox)
{
	return aBoundingBox->contains(vecMin) || aBoundingBox->contains(vecMax);
}