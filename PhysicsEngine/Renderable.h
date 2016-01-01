#pragma once
#include "GeoModel3D.h"
#include "glsl.h"
#include "Camera.h"
#include "RigidBody.h"

//-----------------------------------------------------------------------------
// Name:		Renderable
// Variables:	model - the object model
// Desc:		Groups the behavioural functions of the object with its geometry model
//-----------------------------------------------------------------------------

class Renderable
{
private:
	static GLuint NUMBER_OF_OBJECTS;
	GLuint object_id;
	GeoModel3D* model;
	RigidBody object;
public:
	Renderable(GeoModel3D* model, glm::vec3 position);
	GeoModel3D* getModel();
	glm::mat4 getModelMatrix();
};