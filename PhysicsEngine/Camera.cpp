#include "Camera.h"


Camera::Camera()
{
	fov = 60.0;
	nearZ = 1.0f;
	farZ  = 1000.0f;
	modelMatrix = glm::translate(modelMatrix,glm::vec3(0,0,-30));
}
void Camera::zoom(float increment)
{
	fov += increment;
}
void Camera::rotate(float increment)
{
	modelMatrix = glm::rotate(modelMatrix,increment,glm::vec3(0,1,0));
}

void Camera::translateX(float increment)
{
	modelMatrix = glm::translate(modelMatrix,glm::vec3(increment,0,0));
}

void Camera::translateY(float increment)
{
	modelMatrix = glm::translate(modelMatrix,glm::vec3(0,increment,0));
}

void Camera::translateZ(float increment)
{
	modelMatrix = glm::translate(modelMatrix,glm::vec3(0,0,increment));
}

glm::mat4 Camera::getModelMatrix()
{
	return modelMatrix;
}
glm::mat4 Camera::getViewMatrix()
{
	return viewMatrix;
}
glm::mat4 Camera::getProjectionMatrix()
{
	float aspect = 1.0f;
	projectionMatrix = glm::perspective(fov,aspect,nearZ,farZ);
	return projectionMatrix;
}