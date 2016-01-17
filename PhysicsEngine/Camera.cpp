#include "Camera.h"


Camera::Camera()
{
	fov = 60.0;
	nearZ = 1.0f;
	farZ  = 20.0f;
	model_matrix = glm::translate(model_matrix,glm::vec3(0,0,-10));
}
void Camera::zoom(float increment)
{
	fov += increment;
}
void Camera::rotate(float increment, glm::vec3 rotation_axis)
{
	model_matrix = glm::rotate(model_matrix, increment , rotation_axis);
}

void Camera::translate(glm::vec3 translation)
{
	model_matrix = glm::translate(model_matrix, translation);
}
void Camera::translateX(float increment)
{
	model_matrix = glm::translate(model_matrix,glm::vec3(increment,0,0));
}

void Camera::translateY(float increment)
{
	model_matrix = glm::translate(model_matrix,glm::vec3(0,increment,0));
}

void Camera::translateZ(float increment)
{
	model_matrix = glm::translate(model_matrix,glm::vec3(0,0,increment));
}

glm::mat4 Camera::getMVPMatrix()
{
	return getProjectionMatrix() * view_matrix * model_matrix;
}
glm::mat4 Camera::getModelMatrix()
{
	return model_matrix;
}
glm::mat4 Camera::getViewMatrix()
{
	return view_matrix;
}
glm::mat4 Camera::getProjectionMatrix()
{
	float aspect = 1.0f;
	return glm::perspective(fov,aspect,nearZ,farZ);
}