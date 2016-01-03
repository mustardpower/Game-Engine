#include "RigidBody.h"

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

void RigidBody::setModelMatrix(glm::mat4 matrix)
{
	model_matrix = matrix;
}

void RigidBody::updatePosition(float dt)
{
	physicsHandler.calculatePosition(model_matrix, velocity, dt);
}

glm::vec3 RigidBody::momentum()
{
	return mass * velocity;
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

	tinyxml2::XMLElement* velocityElement = xmlDocument.NewElement("Velocity");
	tinyxml2::XMLText* velocityText = xmlDocument.NewText(glm::to_string(velocity).c_str());
	velocityElement->LinkEndChild(velocityText);
	objElement->LinkEndChild(velocityElement);

	parent->LinkEndChild(objElement);
}