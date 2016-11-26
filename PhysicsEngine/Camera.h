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
	float nearZ, farZ, fov, aspect;
	glm::mat4 model_matrix;
	glm::vec3 cameraPos;
	glm::vec3 cameraTarget;
	glm::vec3 upVector;
public:
	Camera();
	void zoom(float increment);
	void rotate(float increment, glm::vec3 rotation_axis);
	void translate(glm::vec3 translation);
	void translateX(float increment);
	void translateY(float increment);
	void translateZ(float increment);
	glm::vec3 pointOnNearPlane(float x, float y, glm::vec4 viewport);
	glm::vec3 pointOnFarPlane(float x, float y, glm::vec4 viewport);
	void onRotate(float deltaX, float deltaY);
	void onZoom(float deltaX, float deltaY);
	void onPan(float deltaX, float deltaY);
	glm::vec3 Camera::rotatePoint(glm::vec3 point, glm::vec3 origin, glm::vec3 direction, float angle);
	glm::mat4 getMVPMatrix();
	glm::mat4 getModelMatrix();
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
};