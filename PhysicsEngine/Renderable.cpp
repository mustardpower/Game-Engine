#include "Renderable.h"

Renderable::Renderable(GeoModel3D* the_model, glm::vec3 position)
{
	model = the_model;
	/*model->translate(position);*/
}

GeoModel3D* Renderable::getModel()
{
	return model;
}