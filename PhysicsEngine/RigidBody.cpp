#include "RigidBody.h"
#include "UnitsManager.h"

GLuint RigidBody::NUMBER_OF_OBJECTS = 0;
PhysicsHandler RigidBody::physicsHandler;

RigidBody::RigidBody(glm::vec3 position)
{
	object_id = ++NUMBER_OF_OBJECTS;
	translate(position);
}

void RigidBody::translate(glm::vec3 translation)
{
	model_matrix = glm::translate(model_matrix, translation);
}

glm::mat4 RigidBody::getModelMatrix()
{
	return model_matrix;
}

glm::vec3 RigidBody::getMomentum()
{
	return mass * velocity;
}

glm::vec3 RigidBody::getVelocity()
{
	return velocity;
}

void RigidBody::setModelMatrix(glm::mat4 matrix)
{
	model_matrix = matrix;
}

void RigidBody::setVelocity(glm::vec3 v)
{
	velocity = v;
}

void RigidBody::updatePosition(float dt)
{
	physicsHandler.calculatePosition(model_matrix, velocity, dt);
}


void RigidBody::serialize(tinyxml2::XMLDocument &xmlDocument, tinyxml2::XMLNode* parent)
{	
	tinyxml2::XMLElement* objElement = xmlDocument.NewElement("RigidBody");

	// --------------------- Position ----------------------------//
	tinyxml2::XMLElement* positionElement = xmlDocument.NewElement("Position");
	tinyxml2::XMLText* positionText = xmlDocument.NewText(glm::to_string(model_matrix).c_str());
	positionElement->LinkEndChild(positionText);
	objElement->LinkEndChild(positionElement);

	// --------------------- Velocity ----------------------------//

	std::string velocityUnit = UnitsManager::currentUnit(UNIT_LENGTH);
	tinyxml2::XMLElement* velocityElement = xmlDocument.NewElement("Velocity");
	velocityElement->SetAttribute("unit", velocityUnit.c_str());

	tinyxml2::XMLElement* velocityXElement = xmlDocument.NewElement("X");
	tinyxml2::XMLText* velocityXText = xmlDocument.NewText(std::to_string(velocity.x).c_str());
	velocityXElement->LinkEndChild(velocityXText);
	velocityElement->LinkEndChild(velocityXElement);

	tinyxml2::XMLElement* velocityYElement = xmlDocument.NewElement("Y");
	tinyxml2::XMLText* velocityYText = xmlDocument.NewText(std::to_string(velocity.y).c_str());
	velocityYElement->LinkEndChild(velocityYText);
	velocityElement->LinkEndChild(velocityYElement);

	tinyxml2::XMLElement* velocityZElement = xmlDocument.NewElement("Z");
	tinyxml2::XMLText* velocityZText = xmlDocument.NewText(std::to_string(velocity.z).c_str());
	velocityZElement->LinkEndChild(velocityZText);
	velocityElement->LinkEndChild(velocityZElement);

	objElement->LinkEndChild(velocityElement);
	parent->LinkEndChild(objElement);
}

tinyxml2::XMLError RigidBody::deserialize(tinyxml2::XMLNode* parent, RigidBody& rb)
{
	const char* elementText;
	const char* velocityUnit;

	elementText = parent->FirstChildElement("Position")->GetText();
	std::string position(elementText);

	rb.setModelMatrix(glm::from_string_mat4x4(position));

	tinyxml2::XMLElement* velocityElement = parent->FirstChildElement("Velocity");
	velocityUnit = velocityElement->Attribute("unit");
	float velocityX = atof(velocityElement->FirstChildElement("X")->GetText());
	float velocityY = atof(velocityElement->FirstChildElement("Y")->GetText());
	float velocityZ = atof(velocityElement->FirstChildElement("Z")->GetText());
	
	rb.setVelocity(glm::vec3(velocityX, velocityY, velocityZ));
	return tinyxml2::XML_SUCCESS;
}