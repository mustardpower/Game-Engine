#pragma once

#include "glsl.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\ext.hpp"
#include "PhysicsHandler.h"
#include "tinyxml2\tinyxml2.h"

//-----------------------------------------------------------------------------
// Name:		RigidBody
// Variables:	
// Desc:		The physical properties of the object
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

	// getters
	glm::mat4 getModelMatrix();
	glm::vec3 getMomentum();
	glm::vec3 getVelocity();

	// setters
	void setModelMatrix(glm::mat4 matrix);
	void setVelocity(glm::vec3 v);

	void translate(glm::vec3 translation);
	void updatePosition(float dt);

	void serialize(tinyxml2::XMLDocument &xmlDocument, tinyxml2::XMLNode* parent);
	static RigidBody deserialize(tinyxml2::XMLNode* parent);
};
