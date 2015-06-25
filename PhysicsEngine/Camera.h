#pragma once
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
 

//-----------------------------------------------------------------------------
// Name:		Camera
// Variables:	
// Desc:		This class represents a camera style object
//-----------------------------------------------------------------------------
class Camera
{
private:
	float nearZ, farZ, fov;
	glm::mat4 modelMatrix;
	glm::mat4 viewMatrix;
public:
	Camera();
	void zoom(float increment);
	void rotate(float increment);
	void translateX(float increment);
	void translateY(float increment);
	void translateZ(float increment);

	glm::mat4 getModelMatrix();
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
};