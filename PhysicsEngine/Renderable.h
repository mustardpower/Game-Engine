#pragma once
#include "GeoModel3D.h"
#include "glsl.h"
#include "Camera.h"

//-----------------------------------------------------------------------------
// Name:		Renderable
// Variables:	model - the object model
// Desc:		Groups the behavioural functions of the object with its geometry model
//-----------------------------------------------------------------------------

class Renderable
{
private:
	GeoModel3D* model;
public:
	Renderable(char* file_name, glm::vec3 position);
	GeoModel3D* getModel();
};