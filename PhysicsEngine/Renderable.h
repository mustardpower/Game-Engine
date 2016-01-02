#pragma once
#include "GeoModel3D.h"
#include "glsl.h"
#include "Camera.h"
#include "RigidBody.h"
#include "tinyxml2\tinyxml2.h"

//-----------------------------------------------------------------------------
// Name:		Renderable
// Variables:	model - the object model
//				object_id - each object created should have a unique id
//				object - the physics logic behind the physical object it represents
// Desc:		Groups the behavioural functions of the object with its geometry model
//-----------------------------------------------------------------------------

class Renderable
{
private:
	static GLuint NUMBER_OF_OBJECTS;
	GLuint object_id;
	GeoModel3D* model;
	RigidBody object;
	glm::mat4 frame_store;
public:
	Renderable(GeoModel3D* model, glm::vec3 position = glm::vec3(0.0, 0.0, 0.0));
	GeoModel3D* getModel();
	glm::mat4 getModelMatrix();

	void serialize(tinyxml2::XMLDocument &xmlDocument);

	void storeFrame();
	void previousFrame();
	void updateFrame(float dt);
};