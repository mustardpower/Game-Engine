#pragma once

#include "glsl.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\ext.hpp"
#include "PhysicsHandler.h"
#include "tinyxml2\tinyxml2.h"

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
	static PhysicsHandler physicsHandler;
public:
	RigidBody(glm::vec3 position = glm::vec3(0.0,0.0,0.0));
	glm::mat4 getModelMatrix();
	void setModelMatrix(glm::mat4 matrix);
	glm::vec3 momentum();
	void translate(glm::vec3 translation);
	void updatePosition(float dt);
	void serialize(tinyxml2::XMLDocument &xmlDocument);
};
