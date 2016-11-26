#include "Camera.h"

Camera::Camera()
{
	fov = 45.0;
	nearZ = 4.0f;
	farZ  = 60.0f;
	aspect = 1424.0 / 720.0;

	cameraPos = glm::vec3(0.0,0.0,-10.0);
	cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
	upVector = glm::vec3(0.0f, 1.0f, 0.0f);
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
	return getProjectionMatrix() * getViewMatrix() * model_matrix;
}
glm::mat4 Camera::getModelMatrix()
{
	return model_matrix;
}
glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(cameraPos, cameraTarget, upVector);
}
glm::mat4 Camera::getProjectionMatrix()
{
	return glm::perspective(fov, aspect, nearZ, farZ);
}

void Camera::onPan(float deltaX, float deltaY)
{
	glm::vec3 diry = (glm::cross(upVector, cameraTarget - cameraPos)) / (glm::length(glm::cross(upVector, cameraTarget - cameraPos)));

	float length = 2 * glm::length(cameraPos - cameraTarget) * tan(fov / 2.0);
	cameraTarget = cameraTarget + (diry * deltaX * length * aspect) + (upVector * deltaY * length);
}

void Camera::onRotate(float deltaX, float deltaY)
{
	float pi = glm::pi<float>();
	glm::vec3 diry = (glm::cross(upVector, cameraTarget - cameraPos)) / (glm::length(glm::cross(upVector, cameraTarget - cameraPos)));
	cameraPos = rotatePoint(cameraPos, cameraTarget, upVector, -deltaX * pi);
	cameraPos = rotatePoint(cameraPos, cameraTarget, diry, deltaY * pi);
	upVector = rotatePoint(cameraTarget + upVector, cameraTarget, diry, deltaY * pi) - cameraTarget;
	upVector = glm::normalize(upVector);
}

void Camera::onZoom(float deltaX, float deltaY)
{
	cameraPos = cameraTarget + (cameraPos - cameraTarget) * (deltaY + 1);
}

glm::vec3 Camera::rotatePoint(glm::vec3 point, glm::vec3 origin, glm::vec3 direction, float angle)
{
	glm::vec3 rotatedPoint;
	const float C = 1 - cos(angle);
	const float c = cos(angle);
	const float s = sin(angle);

	float e00 = direction.x * direction.x * C + c;
	float e01 = direction.x * direction.y * C - direction.z * s;
	float e02 = direction.x * direction.z * C + direction.y *s;

	float e10 = direction.y * direction.x * C + direction.z *s;
	float e11 = direction.y * direction.y * C + c;
	float e12 = direction.y * direction.z * C - direction.x *s;

	float e20 = direction.z * direction.x * C - direction.y *s;
	float e21 = direction.z * direction.y * C + direction.x * s;
	float e22 = direction.z * direction.z * C + c;

	glm::mat3 rotationMatrix = glm::mat3(e00, e01, e02, e10, e11, e12, e20, e21, e22);
	glm::vec3 result = origin + rotationMatrix * (point - origin);
	return result;
}

glm::vec3 Camera::pointOnNearPlane(float x, float y, glm::vec4 viewport)
{
	glm::vec3 worldPosNear;
	glm::mat4 modelView = getViewMatrix() * model_matrix;
	glm::mat4 projection_matrix = getProjectionMatrix();
	glm::vec3 screenPos = glm::vec3(x, y, 0.0f);
	worldPosNear = glm::unProject(screenPos, modelView, projection_matrix, viewport);
	return worldPosNear;
}

glm::vec3 Camera::pointOnFarPlane(float x, float y, glm::vec4 viewport)
{
	glm::vec3 worldPosFar;
	glm::mat4 modelView = getViewMatrix() * model_matrix;
	glm::mat4 projection_matrix = getProjectionMatrix();
	glm::vec3 screenPos = glm::vec3(x, y, 1.0f);
	worldPosFar = glm::unProject(screenPos, modelView, projection_matrix, viewport);
	return worldPosFar;
}