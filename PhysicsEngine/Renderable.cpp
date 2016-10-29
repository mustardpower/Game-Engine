#include "Renderable.h"
#include <utility>

GLuint Renderable::NUMBER_OF_OBJECTS = 0;

Renderable::Renderable()
{
	selected = false;
}

Renderable::Renderable(const Renderable &other)
{
	model = other.getModel();
	object_id = ++NUMBER_OF_OBJECTS;
	object = other.object;
	selected = other.selected;
}
Renderable::Renderable(GeoModel3D the_model, RigidBody rb)
{
	object_id = ++NUMBER_OF_OBJECTS;
	model = the_model;
	object = rb;
	selected = false;
}

Renderable & Renderable::operator= (const Renderable & other)
{
	model = other.model;
	object_id = ++NUMBER_OF_OBJECTS;
	object = other.object;
	selected = other.selected;

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

AABB Renderable::getBoundingBox()
{
	return boundingBox;
}

void Renderable::setModelMatrix(glm::mat4x4 modelMatrix)
{
	object.setModelMatrix(modelMatrix);
}

void Renderable::setModel(GeoModel3D aModel)
{
	model = aModel;
}

void Renderable::setRigidBody(RigidBody rigidBody)
{
	object = rigidBody;
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

tinyxml2::XMLError Renderable::deserialize(tinyxml2::XMLNode* parent, Renderable& renderable)
{
	tinyxml2::XMLError result;
	GeoModel3D model;
	tinyxml2::XMLNode* pGeoModel = parent->FirstChildElement("GEOModel");
	result = GeoModel3D::deserialize(pGeoModel, model);
	if (result != tinyxml2::XML_SUCCESS)
	{
		return result;
	};

	RigidBody rigidBody;
	tinyxml2::XMLNode* pRigidBody = parent->FirstChildElement("RigidBody");
	result = RigidBody::deserialize(pRigidBody, rigidBody);
	if (result != tinyxml2::XML_SUCCESS)
	{
		return result;
	};

	renderable.setModel(model);
	renderable.setRigidBody(rigidBody);

	return tinyxml2::XML_SUCCESS;
}

bool Renderable::intersects(glm::vec3 origin, glm::vec3 dir)
{
	return boundingBox.intersects(origin, dir);
}

void Renderable::setSelection(bool is_selected)
{
	selected = is_selected;
}

bool Renderable::isSelected()
{
	return selected;
}

void Renderable::print()
{
	std::cout << "Object ID: " << object_id << std::endl;
	model.print();
}