#include "BoundingSphere.h"

bool BoundingSphere::contains(glm::vec3 point)
{
	return ((origin.x-point.x)*(origin.x-point.x)
		+(origin.y-point.y)*(origin.y-point.y)
		+(origin.z-point.z)*(origin.z-point.z) < (radius*radius));	
}