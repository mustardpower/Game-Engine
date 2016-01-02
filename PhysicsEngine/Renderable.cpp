#include "Renderable.h"

GLuint Renderable::NUMBER_OF_OBJECTS = 0;

Renderable::Renderable(GeoModel3D* the_model, glm::vec3 position)
{
	object_id = ++NUMBER_OF_OBJECTS;
	model = the_model;
	object = RigidBody(position);
}

GeoModel3D* Renderable::getModel()
{
	return model;
}

glm::mat4 Renderable::getModelMatrix()
{
	return object.getModelMatrix();
}

void Renderable::updateFrame(float dt)
{
	object.updatePosition(dt);
}