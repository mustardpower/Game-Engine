#include "Renderable.h"

Renderable::Renderable(char* file_name, glm::vec3 position)
{
	model = new GeoModel3D(file_name);
	model->translate(position);
}

GeoModel3D* Renderable::getModel()
{
	return model;
}