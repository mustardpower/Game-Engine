#pragma once
#include "qmatrix4x4.h"
#include "qvector3d.h"
#include "GeoModel3D.h"
#include "RigidBody.h"
#include "AABB.h"
#include "tinyxml2\tinyxml2.h"

//-----------------------------------------------------------------------------
// Name:		Renderable
// Variables:	model - the object model
//				object_id - each object created should have a unique id
//				object - the physics logic behind the physical object it represents
// Desc:		Groups the behavioural functions of the object with its geometry model
//-----------------------------------------------------------------------------

class Renderable
{
private:
	static int NUMBER_OF_OBJECTS;
	int object_id;
	GeoModel3D model;
	RigidBody object;
	QMatrix4x4 frame_store;
	AABB boundingBox;
	bool selected;
public:
	Renderable();
	Renderable(const Renderable& other);
	Renderable & operator= (const Renderable & other);
	bool operator==(const Renderable& other);
	bool operator!=(const Renderable& other);
	Renderable(GeoModel3D model, RigidBody rigidBody);

	AABB calculateBoundingBox();
	float getMass();
	GeoModel3D getModel() const;
	QMatrix4x4 getModelMatrix() const;
	QVector3D getVelocity();
	AABB getBoundingBox();
	bool equalTo(const Renderable& other);
	bool isSelected();
	bool intersects(Renderable other);
	bool intersects(QVector3D p, QVector3D dir);
	void previousFrame();
	void serialize(tinyxml2::XMLDocument &xmlDocument, tinyxml2::XMLNode* parent);
	void setModelMatrix(QMatrix4x4 modelMatrix);
	void setModel(GeoModel3D aModel);
	void setRigidBody(RigidBody rigidBody);
	void setSelection(bool is_selected);
	void setVelocity(QVector3D velocity);
	void storeFrame();
	static tinyxml2::XMLError deserialize(tinyxml2::XMLNode* parent, Renderable& renderable);
	void translate(QVector3D translation);
	void updateFrame(float dt);

	void print();
};