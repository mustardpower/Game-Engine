#include "PhysicsHandler.h"
#include <iostream>

const glm::vec3 PhysicsHandler::gravity(0.0,9.81,0.0); // in N/kg
void PhysicsHandler::calculatePosition(glm::mat4 &modelmat, glm::vec3 velocity,float dt)
{
	modelmat = glm::translate(modelmat, velocity * dt);
}

glm::vec3 totalMomentum(float mass1, glm::vec3 velocity1, float mass2, glm::vec3 velocity2)
{
	return mass1 * velocity1 + mass2 * velocity2;
}

glm::vec3 PhysicsHandler::linePlaneCollisionPoint(glm::vec3 lo, glm::vec3 ldir, glm::vec3 ppoint, glm::vec3 pnormal)
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
	float numerator = glm::dot((ppoint - lo), pnormal);
	float denom = glm::dot(ldir, pnormal);
	d = numerator / denom;
	return ldir * d + lo;
}