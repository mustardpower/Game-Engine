#include "PhysicsHandler.h"
#include <iostream>

const glm::vec3 PhysicsHandler::gravity(0.0,9.81,0.0); // in N/kg
void PhysicsHandler::calculatePosition(glm::mat4 &modelmat, glm::vec3 velocity,float dt)
{
	modelmat = glm::translate(modelmat, velocity * dt);
}