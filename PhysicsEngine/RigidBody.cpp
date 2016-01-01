#include "RigidBody.h"

GLuint RigidBody::NUMBER_OF_OBJECTS = 0;

RigidBody::RigidBody(glm::vec3 position)
{
	object_id = ++NUMBER_OF_OBJECTS;
	translate(position);
}

void RigidBody::translate(glm::vec3 translation)
{
	model_matrix = glm::translate(model_matrix, translation);
}

glm::mat4 RigidBody::getModelMatrix()
{
	return model_matrix;
}