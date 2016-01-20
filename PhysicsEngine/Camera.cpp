#include "Camera.h"


Camera::Camera()
{
	fov = 45.0;
	nearZ = 4.0f;
	farZ  = 60.0f;

	glm::vec3 cameraPos = glm::vec3(0.0,0.0,-10.0);
	glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	view_matrix = glm::lookAt(cameraPos,cameraTarget,glm::vec3(0.0f, 1.0f, 0.0f));

	float aspect = 1.0f;
	projection_matrix = glm::perspective(fov, aspect, nearZ, farZ);
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
	return projection_matrix * view_matrix * model_matrix;
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
	return projection_matrix;
}