#pragma once
#include "qmatrix4x4.h"
#include "qvector3d.h"
#include "PhysicsHandler.h"
#include "tinyxml2\tinyxml2.h"

//-----------------------------------------------------------------------------
// Name:		RigidBody
// Variables:	NUMBER_OF_OBJECTS - number of objects still active
//				objectID - the unique id associated with the object
//				model_matrix - stores any transformations applied to the model
//				mass, inertia, velocity etc - self explanatory	
//				physicsHandler - used to calculate any collisions and physical interactions
// Desc:		The physical properties of the object
//-----------------------------------------------------------------------------

class RigidBody
{
private:
	static int NUMBER_OF_OBJECTS;
	int object_id;
	QVector3D angular_velocity; // radians / s
	QMatrix4x4 inertia; // in kgm^2
	QMatrix4x4 model_matrix;
	float mass;	// in kilograms (kg)
	QVector3D velocity;	// in m / s
	static PhysicsHandler physicsHandler;
public:

	RigidBody(QVector3D position = QVector3D(0.0,0.0,0.0), float mass = 1.0);

	// getters
	QVector3D getAngularVelocity();
	QMatrix4x4 getInertia();
	float getMass() const;
	QMatrix4x4 getModelMatrix() const;
	QVector3D getMomentum();
	QVector3D getVelocity();

	// setters
	void setAngularVelocity(QVector3D angV);
	void setMass(float object_mass);
	void setModelMatrix(QMatrix4x4 matrix);
	void setVelocity(QVector3D v);

	bool equalTo(const RigidBody &other);
	void translate(QVector3D translation);
	void updatePosition(float dt);

	void serialize(tinyxml2::XMLDocument &xmlDocument, tinyxml2::XMLNode* parent);
	static QString toString(QMatrix4x4 aMatrix);
	static QMatrix4x4 fromString(QString aString);
	static tinyxml2::XMLError deserialize(tinyxml2::XMLNode* parent, RigidBody& rigidBody);
	static QVector3D deserializeVector3D(tinyxml2::XMLNode* parent, const char* elementName);
};
