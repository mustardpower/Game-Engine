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
Renderable::Renderable(GeoModel3D the_model, RigidBody rb)
{
	object_id = ++NUMBER_OF_OBJECTS;
	model = the_model;
	object = rb;
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

glm::vec3 Renderable::getVelocity()
{
	return object.getVelocity();
}

void Renderable::setModelMatrix(glm::mat4x4 modelMatrix)
{
	object.setModelMatrix(modelMatrix);
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
	tinyxml2::XMLNode* pRigidBody = parent->FirstChildElement("RigidBody");
	RigidBody rigidBody = RigidBody::deserialize(pRigidBody);
	Renderable object(model,rigidBody);
	return object;
}

bool Renderable::intersects(glm::vec3 origin, glm::vec3 dir)
{
	return boundingBox.intersects(origin, dir);
}