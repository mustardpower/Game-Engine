#include "RigidBody.h"
#include "UnitsManager.h"
#include <sstream>

int RigidBody::NUMBER_OF_OBJECTS = 0;
PhysicsHandler RigidBody::physicsHandler;

RigidBody::RigidBody(QVector3D position, float object_mass)
{
	object_id = ++NUMBER_OF_OBJECTS;
	translate(position);
	mass = object_mass;
}

bool RigidBody::equalTo(const RigidBody & other)
{
	if (mass != other.mass) return false;
	if (model_matrix != other.model_matrix) return false;
	if (velocity != other.velocity) return false;
	if (inertia != other.inertia) return false;
	if (angular_velocity != other.angular_velocity) return false;
	return true;
}

void RigidBody::translate(QVector3D translation)
{
	model_matrix.translate(translation);
}

float RigidBody::getMass() const
{
	return mass;
}

QMatrix4x4 RigidBody::getModelMatrix() const
{
	return model_matrix;
}

QVector3D RigidBody::getMomentum()
{
	return mass * velocity;
}

QVector3D RigidBody::getVelocity()
{
	return velocity;
}

void RigidBody::setMass(float object_mass)
{
	mass = object_mass;
}

void RigidBody::setModelMatrix(QMatrix4x4 matrix)
{
	model_matrix = matrix;
}

void RigidBody::setVelocity(QVector3D v)
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

	// --------------------- Mass ----------------------------//
	tinyxml2::XMLElement* massElement = xmlDocument.NewElement("Mass");
	tinyxml2::XMLText* massText = xmlDocument.NewText(std::to_string(mass).c_str());
	massElement->LinkEndChild(massText);
	objElement->LinkEndChild(massElement);

	// --------------------- Position ----------------------------//
	tinyxml2::XMLElement* positionElement = xmlDocument.NewElement("Position");
	tinyxml2::XMLText* positionText = xmlDocument.NewText(toString(model_matrix).toUtf8().constData());
	positionElement->LinkEndChild(positionText);
	objElement->LinkEndChild(positionElement);

	// --------------------- Velocity ----------------------------//

	std::string velocityUnit = UnitsManager::currentUnit(UNIT_LENGTH);
	tinyxml2::XMLElement* velocityElement = xmlDocument.NewElement("Velocity");
	velocityElement->SetAttribute("unit", velocityUnit.c_str());

	tinyxml2::XMLElement* velocityXElement = xmlDocument.NewElement("X");
	tinyxml2::XMLText* velocityXText = xmlDocument.NewText(std::to_string(velocity.x()).c_str());
	velocityXElement->LinkEndChild(velocityXText);
	velocityElement->LinkEndChild(velocityXElement);

	tinyxml2::XMLElement* velocityYElement = xmlDocument.NewElement("Y");
	tinyxml2::XMLText* velocityYText = xmlDocument.NewText(std::to_string(velocity.y()).c_str());
	velocityYElement->LinkEndChild(velocityYText);
	velocityElement->LinkEndChild(velocityYElement);

	tinyxml2::XMLElement* velocityZElement = xmlDocument.NewElement("Z");
	tinyxml2::XMLText* velocityZText = xmlDocument.NewText(std::to_string(velocity.z()).c_str());
	velocityZElement->LinkEndChild(velocityZText);
	velocityElement->LinkEndChild(velocityZElement);

	objElement->LinkEndChild(velocityElement);
	parent->LinkEndChild(objElement);
}

tinyxml2::XMLError RigidBody::deserialize(tinyxml2::XMLNode* parent, RigidBody& rb)
{
	const char* elementText;

	tinyxml2::XMLElement* massElement = parent->FirstChildElement("Mass");
	if (massElement)
	{
		float mass = atof(massElement->GetText());
		rb.setMass(mass);
	}

	elementText = parent->FirstChildElement("Position")->GetText();
	QString position(elementText);

	rb.setModelMatrix(fromString(position));

	tinyxml2::XMLElement* velocityElement = parent->FirstChildElement("Velocity");
	float velocityX = atof(velocityElement->FirstChildElement("X")->GetText());
	float velocityY = atof(velocityElement->FirstChildElement("Y")->GetText());
	float velocityZ = atof(velocityElement->FirstChildElement("Z")->GetText());

	rb.setVelocity(QVector3D(velocityX, velocityY, velocityZ));
	return tinyxml2::XML_SUCCESS;
}

QString RigidBody::toString(QMatrix4x4 aMatrix)
{
	float data[16] = { 0 };
	memcpy(&data, aMatrix.constData(), 16 * sizeof(float));
	std::ostringstream stream;
	for (float *p = data; p < data + 16; p++)
	{
		stream << *p <<" ";
	}
	return QString(stream.str().c_str());
}

QMatrix4x4 RigidBody::fromString(QString aString)
{
	float x[4];
	float y[4];
	float z[4];
	float w[4];

	QTextStream values(&aString);
	values >> x[0] >> x[1] >> x[2] >> x[3] >> y[0] >> y[1] >> y[2] >> y[3] >> z[0] >> z[1] >> z[2] >> z[3] >> w[0] >> w[1] >> w[2] >> w[3];
	return QMatrix4x4(x[0], y[0], z[0], w[0], x[1], y[1], z[1], w[1], x[2], y[2], z[2], w[2], x[3], y[3], z[3], w[3]);
}