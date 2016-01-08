#include "Renderable.h"
#include <utility>

GLuint Renderable::NUMBER_OF_OBJECTS = 0;

Renderable::Renderable()
{
}

Renderable::Renderable(const Renderable &other)
{
	model = other.getModel();
	object_id = ++NUMBER_OF_OBJECTS;
	object = other.object;
}
Renderable::Renderable(GeoModel3D the_model, glm::vec3 position)
{
	object_id = ++NUMBER_OF_OBJECTS;
	model = the_model;
	object = RigidBody(position);
}

Renderable & Renderable::operator= (const Renderable & other)
{
	model = other.model;
	object_id = ++NUMBER_OF_OBJECTS;
	object = other.object;

	return *this;
}

GeoModel3D Renderable::getModel() const
{
	return model;
}

glm::mat4 Renderable::getModelMatrix()
{
	return object.getModelMatrix();
}

void Renderable::storeFrame()
{
	frame_store = object.getModelMatrix();
}

void Renderable::updateFrame(float dt)
{
	object.updatePosition(dt);
}

void Renderable::previousFrame()
{
	object.setModelMatrix(frame_store);
}

void Renderable::serialize(tinyxml2::XMLDocument &xmlDocument, tinyxml2::XMLNode* parent)
{
	tinyxml2::XMLElement* objElement = xmlDocument.NewElement("Renderable");
	model.serialize(xmlDocument, objElement);
	object.serialize(xmlDocument, objElement);
	parent->LinkEndChild(objElement);
}

Renderable Renderable::deserialize(tinyxml2::XMLNode* parent)
{
	tinyxml2::XMLNode* pGeoModel = parent->FirstChildElement("GEOModel");
	GeoModel3D model = GeoModel3D::deserialize(pGeoModel);
	Renderable object(model);
	return object;
}