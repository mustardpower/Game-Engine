#pragma once

#include "glsl.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

//-----------------------------------------------------------------------------
// Name:		Renderable
// Variables:	model - the object model
// Desc:		Groups the behavioural functions of the object with its geometry model
//-----------------------------------------------------------------------------

class RigidBody
{
private:
	static GLuint NUMBER_OF_OBJECTS;
	GLuint object_id;
	glm::mat4 model_matrix;
	glm::float32 mass;	// in kilograms (kg)
	glm::vec3 inertia; // in kgm^2
	glm::vec3 velocity;	// in m / s
	glm::vec3 angular_velocity; // radians / s
public:
	RigidBody() {};
	RigidBody(glm::vec3 position);
	glm::mat4 getModelMatrix();
	void translate(glm::vec3 translation);
};
