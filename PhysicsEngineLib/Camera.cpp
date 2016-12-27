#include "Camera.h"
#include "qmath.h"

Camera::Camera()
{
	fov = 45.0;
	nearZ = 4.0f;
	farZ  = 60.0f;
	aspect = 1424.0 / 720.0;

	cameraPos = QVector3D(0.0,0.0,-10.0);
	cameraTarget = QVector3D(0.0f, 0.0f, 0.0f);
	upVector = QVector3D(0.0f, 1.0f, 0.0f);
}
void Camera::zoom(float increment)
{
	fov += increment;
}
void Camera::rotate(float increment, QVector3D rotation_axis)
{
	model_matrix.rotate(increment, rotation_axis);
}

void Camera::translate(QVector3D translation)
{
	model_matrix.translate(translation);
}
void Camera::translateX(float increment)
{
	model_matrix.translate(QVector3D(increment, 0, 0));
}

void Camera::translateY(float increment)
{
	model_matrix.translate(QVector3D(0, increment, 0));
}

void Camera::translateZ(float increment)
{
	model_matrix.translate(QVector3D(0, 0, increment));
}

QMatrix4x4 Camera::getMVPMatrix()
{
	return getProjectionMatrix() * getViewMatrix() * model_matrix;
}
QMatrix4x4 Camera::getModelMatrix()
{
	return model_matrix;
}
QMatrix4x4 Camera::getViewMatrix()
{
	QMatrix4x4 mat;
	mat.lookAt(cameraPos, cameraTarget, upVector);
	return mat;
}
QMatrix4x4 Camera::getProjectionMatrix()
{
	QMatrix4x4 mat;
	mat.perspective(fov, aspect, nearZ, farZ);
	return mat;
}

void Camera::onPan(float deltaX, float deltaY)
{
	QVector3D denom = QVector3D::crossProduct(upVector, cameraTarget - cameraPos);
	QVector3D diry = (QVector3D::crossProduct(upVector, cameraTarget - cameraPos)) / (denom.length());

	float length = 2 * (((cameraPos - cameraTarget) * tan(fov / 2.0)).length());
	cameraTarget = cameraTarget + (diry * deltaX * length * aspect) + (upVector * deltaY * length);
}

void Camera::onRotate(float deltaX, float deltaY)
{
	float pi = float(M_PI);
	QVector3D diry = (QVector3D::crossProduct(upVector, cameraTarget - cameraPos)) / ((QVector3D::crossProduct(upVector, cameraTarget - cameraPos)).length());
	cameraPos = rotatePoint(cameraPos, cameraTarget, upVector, -deltaX * pi);
	cameraPos = rotatePoint(cameraPos, cameraTarget, diry, deltaY * pi);
	upVector = rotatePoint(cameraTarget + upVector, cameraTarget, diry, deltaY * pi) - cameraTarget;
	upVector.normalize();
}

void Camera::onZoom(float deltaX, float deltaY)
{
	cameraPos = cameraTarget + (cameraPos - cameraTarget) * (deltaY + 1);
}

QVector3D Camera::rotatePoint(QVector3D point, QVector3D origin, QVector3D direction, float angle)
{
	QVector3D rotatedPoint;
	const float C = 1 - cos(angle);
	const float c = cos(angle);
	const float s = sin(angle);

	float e00 = direction.x() * direction.x() * C + c;
	float e01 = direction.x() * direction.y() * C - direction.z() * s;
	float e02 = direction.x() * direction.z() * C + direction.y() *s;

	float e10 = direction.y() * direction.x() * C + direction.z() *s;
	float e11 = direction.y() * direction.y() * C + c;
	float e12 = direction.y() * direction.z() * C - direction.x() *s;

	float e20 = direction.z() * direction.x() * C - direction.y() *s;
	float e21 = direction.z() * direction.y() * C + direction.x() * s;
	float e22 = direction.z() * direction.z() * C + c;

	float values[16] = { e00, e01, e02, 0.0, e10, e11, e12, 0.0, e20, e21, e22, 0.0, 0.0, 0.0, 0.0, 1.0 };
	QMatrix4x4 rotationMatrix(values);
	QVector3D result = origin + rotationMatrix * (point - origin);
	return result;
}

QVector3D Camera::pointOnNearPlane(float x, float y, QRect viewport)
{
	QVector3D worldPosNear(x,y,0.0);
	QMatrix4x4 modelView = getViewMatrix() * model_matrix;
	QMatrix4x4 projection_matrix = getProjectionMatrix();
	return worldPosNear.unproject(modelView, projection_matrix, viewport);
}

QVector3D Camera::pointOnFarPlane(float x, float y, QRect viewport)
{
	QVector3D worldPosFar(x, y, 1.0);
	QMatrix4x4 modelView = getViewMatrix() * model_matrix;
	QMatrix4x4 projection_matrix = getProjectionMatrix();
	return worldPosFar.unproject(modelView, projection_matrix, viewport);
}

void Camera::resizeViewport(int width, int height)
{
	aspect = width / (float)height;
}
