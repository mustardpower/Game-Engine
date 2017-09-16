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

float PhysicsHandler::calculateReactionForce(QVector3D r1, QVector3D r2, QMatrix4x4 i1, QMatrix4x4 i2, float m1, float m2, float e, QVector3D contactNormal, QVector3D vr)
{
	// r1 offset from contact point to centre of mass on colliding body 1
	// r2 offset from contact point to centre of mass on colliding body 2
	// e - coefficient of restitution

	QMatrix4x4 invInertiaTensor1 = i1.inverted();
	QMatrix4x4 invInertiaTensor2 = i2.inverted();
	QVector3D k1 = invInertiaTensor1 * QVector3D::crossProduct((QVector3D::crossProduct(r1, contactNormal)), r1);
	QVector3D k2 = invInertiaTensor2 * QVector3D::crossProduct((QVector3D::crossProduct(r2, contactNormal)), r2);

	float jr = QVector3D::dotProduct(-(1 + e) * vr, contactNormal) /
		((1 / m1) + (1 / m2) + QVector3D::dotProduct(k1 + k2, contactNormal));
	return jr;
}

QVector3D PhysicsHandler::calculateRelativeVelocity(QVector3D v1, QVector3D v2, QVector3D w1, QVector3D w2, QVector3D r1, QVector3D r2)
{
	QVector3D vp1 = v1 + QVector3D::crossProduct(w1, r1);
	QVector3D vp2 = v2 + QVector3D::crossProduct(w2, r2);
	return vp2 - vp1;
}

QVector3D PhysicsHandler::calculateLinearVelocity(QVector3D v, float jr, float m, QVector3D contactNormal)
{
	return v + (jr / m) * contactNormal;
}