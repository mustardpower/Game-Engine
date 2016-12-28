#include "PhysicsHandler.h"

const QVector3D PhysicsHandler::gravity(0.0,9.81,0.0); // in N/kg

void PhysicsHandler::calculatePosition(QMatrix4x4 &modelmat, QVector3D velocity,float dt)
{
	modelmat.translate(velocity * dt);
}

QVector3D totalMomentum(float mass1, QVector3D velocity1, float mass2, QVector3D velocity2)
{
	return mass1 * velocity1 + mass2 * velocity2;
}

QVector3D PhysicsHandler::linePlaneCollisionPoint(QVector3D lo, QVector3D ldir, QVector3D ppoint, QVector3D pnormal)
{
	/*
	lo - a point that lies on the line
	ldir - a vector in the direction of the line
	ppoint - a point that lies on the plane
	pnormal - a normal vector to the plane

	If denominator is zero then the line and plane are parallel
	If the denominator is also zero then the line is contained within the plane, else they do not intersect
	
	if the denominator is non zero there is one intersection point given by ldir * d + lo*/
	 
	float d;	
	float numerator = QVector3D::dotProduct((ppoint - lo), pnormal);
	float denom = QVector3D::dotProduct(ldir, pnormal);
	d = numerator / denom;
	return ldir * d + lo;
}

// fire a Box A from origin Oa and fire Box B from origin Ob so that they collide

// at each time step check for collision

// THIS IS THE FIRST STEP!!!!! NEED TO WORK OUT WHEN OBJECTS ARE ACTUALLY IN COLLISION
// bounding box test - if colliding then do a more computationally expensive test
// for our cubes we may get away with the simple bounding box test
// need to check if the AABB calculation is correct when the box is rotated!

/* if colliding then resolve constraints

- will need to resolve positions so that faces are not intersecting
- when collision is detected then apply new forces to Box A and Box B so that faces no longer collide (so distance between colliding faces\planes is 0) 
*/