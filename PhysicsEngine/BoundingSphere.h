#include "BoundingObject.h"

class BoundingSphere : public BoundingObject
{
private:
	glm::vec3 origin;
	float radius;

public:
	BoundingSphere(glm::vec3 _origin,float _radius) { origin = _origin; radius = _radius; }
	bool contains(glm::vec3 point);
};