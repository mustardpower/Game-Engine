#include "Renderable.h"

GLuint Renderable::NUMBER_OF_OBJECTS = 0;

Renderable::Renderable(GeoModel3D* the_model, glm::vec3 position)
{
	object_id = ++NUMBER_OF_OBJECTS;
	model = the_model;
	translate(position);
}

GeoModel3D* Renderable::getModel()
{
	return model;
}

void Renderable::translate(glm::vec3 translation)
{
	model_matrix = glm::translate(model_matrix,translation);
}

glm::mat4 Renderable::getModelMatrix()
{
	return model_matrix;
}