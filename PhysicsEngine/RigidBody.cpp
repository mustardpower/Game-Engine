#include "RigidBody.h"

GLuint RigidBody::NUMBER_OF_OBJECTS = 0;
PhysicsHandler RigidBody::physicsHandler;

RigidBody::RigidBody(glm::vec3 position)
{
	object_id = ++NUMBER_OF_OBJECTS;
	translate(position);
	velocity = glm::vec3(0.0, 0.0, 0.0);
}

void RigidBody::translate(glm::vec3 translation)
{
	model_matrix = glm::translate(model_matrix, translation);
}

glm::mat4 RigidBody::getModelMatrix()
{
	return model_matrix;
}

void RigidBody::updatePosition(float dt)
{
	physicsHandler.calculatePosition(model_matrix, velocity, dt);
}