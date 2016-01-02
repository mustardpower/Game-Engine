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