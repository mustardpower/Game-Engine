#pragma once
#include "GeoModel3D.h"
#include "glsl.h"
#include "Camera.h"
#include "RigidBody.h"
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
	static GLuint NUMBER_OF_OBJECTS;
	GLuint object_id;
	GeoModel3D model;
	RigidBody object;
	glm::mat4 frame_store;
	AABB boundingBox;
	bool selected;
public:
	Renderable();
	Renderable(const Renderable& other);
	Renderable & operator= (const Renderable & other);
	Renderable(GeoModel3D model, RigidBody rigidBody);

	GeoModel3D getModel() const;
	glm::mat4 getModelMatrix();
	glm::vec3 getVelocity();

	void setModelMatrix(glm::mat4x4 modelMatrix);
	void setModel(GeoModel3D aModel);
	void setRigidBody(RigidBody rigidBody);

	void serialize(tinyxml2::XMLDocument &xmlDocument, tinyxml2::XMLNode* parent);
	static tinyxml2::XMLError deserialize(tinyxml2::XMLNode* parent, Renderable& renderable);

	void storeFrame();
	void previousFrame();
	void updateFrame(float dt);

	bool Renderable::intersects(glm::vec3 p, glm::vec3 dir);

	void setSelection(bool is_selected);
	bool isSelected();

	void print();
};