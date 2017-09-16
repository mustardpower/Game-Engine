#include "Renderable.h"
#include <iostream>

int Renderable::NUMBER_OF_OBJECTS = 0;

Renderable::Renderable()
{
	selected = false;
	object_id = ++NUMBER_OF_OBJECTS;
}

Renderable::Renderable(const Renderable &other)
{
	model = other.getModel();
	object_id = ++NUMBER_OF_OBJECTS;
	object = other.object;
	selected = other.selected;
	boundingBox = other.boundingBox;
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
	boundingBox = other.boundingBox;

	return *this;
}

bool Renderable::operator==(const Renderable& other)
{
	return object_id == other.object_id;
}

bool Renderable::operator!=(const Renderable& other)
{
	return object_id != other.object_id;
}

bool Renderable::equalTo(const Renderable& other)
{
	return object.equalTo(other.object);
}

QVector3D Renderable::getAngularVelocity()
{
	return object.getAngularVelocity();
}

QMatrix4x4 Renderable::getInertia()
{
	return object.getInertia();
}

float Renderable::getMass()
{
	return object.getMass();
}

GeoModel3D Renderable::getModel() const
{
	return model;
}

QMatrix4x4 Renderable::getModelMatrix() const
{
	return object.getModelMatrix();
}

QVector3D Renderable::getVelocity()
{
	return object.getVelocity();
}

AABB Renderable::getBoundingBox()
{
	boundingBox = calculateBoundingBox();
	return boundingBox;
}

AABB Renderable::calculateBoundingBox()
{
	AABB box;
	QVector3D vecMin, vecMax;
	QVector<GLModel3DData> meshes = model.retrieveMeshes();
	
	if (!meshes.empty())
	{
		GLModel3DData modelData = meshes.first();
		vecMin.setX(modelData.getMeshData().positions[0]);
		vecMin.setY(modelData.getMeshData().positions[1]);
		vecMin.setZ(modelData.getMeshData().positions[2]);
		vecMin = object.getModelMatrix() * vecMin;
		vecMax = vecMin;
	}

	for (QVector<GLModel3DData>::iterator mesh = meshes.begin(); mesh != meshes.end(); mesh++)
	{
		std::vector<float> positions = mesh->getMeshData().positions;
		for (std::vector<float>::iterator pos = positions.begin(); pos != positions.end(); pos = pos + 3)
		{
			QVector3D current(*pos, *(pos + 1), *(pos + 2));
			QMatrix4x4 modelTransform = object.getModelMatrix();
			QVector3D transformedVec = modelTransform * current;

			if (vecMin.x() > transformedVec.x()) vecMin.setX(transformedVec.x());
			if (vecMax.x() < transformedVec.x()) vecMax.setX(transformedVec.x());
			if (vecMin.y() > transformedVec.y()) vecMin.setY(transformedVec.y());
			if (vecMax.y() < transformedVec.y()) vecMax.setY(transformedVec.y());
			if (vecMin.z() > transformedVec.z()) vecMin.setZ(transformedVec.z());
			if (vecMax.z() < transformedVec.z()) vecMax.setZ(transformedVec.z());
		}
	}

	box.setDimensions(vecMin, vecMax);
	return box;
}

void Renderable::setModelMatrix(QMatrix4x4 modelMatrix)
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

void Renderable::translate(QVector3D translation)
{
	object.translate(translation);
}

bool Renderable::intersects(QVector3D origin, QVector3D dir)
{
	return boundingBox.intersects(origin, dir);
}

bool Renderable::intersects(Renderable other)
{
	return getBoundingBox().intersects(other.getBoundingBox());
}

void Renderable::setSelection(bool is_selected)
{
	selected = is_selected;
}

void Renderable::setSelectionIfRayIntersects(QVector3D pos, QVector3D rayDirection)
{
	selected = intersects(pos, rayDirection);
}

void Renderable::setVelocity(QVector3D velocity)
{
	object.setVelocity(velocity);
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