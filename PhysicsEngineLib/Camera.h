#pragma once
#include "qmatrix4x4.h"
#include "qvector3d.h"
#include "qvector4d.h"
 

//-----------------------------------------------------------------------------
// Name:		Camera
// Variables:	
// Desc:		This class represents a camera style object
//-----------------------------------------------------------------------------

class Camera
{
private:
	float nearZ, farZ, fov, aspect;
	QMatrix4x4 model_matrix;
	QVector3D cameraPos;
	QVector3D cameraTarget;
	QVector3D upVector;
public:
	Camera();
	QVector3D Camera::rotatePoint(QVector3D point, QVector3D origin, QVector3D direction, float angle);
	QMatrix4x4 getMVPMatrix();
	QMatrix4x4 getModelMatrix();
	QMatrix4x4 getViewMatrix();
	QMatrix4x4 getProjectionMatrix();
	void onRotate(float deltaX, float deltaY);
	void onZoom(float deltaX, float deltaY);
	void onPan(float deltaX, float deltaY);
	QVector3D pointOnNearPlane(float x, float y, QRect viewport);
	QVector3D pointOnFarPlane(float x, float y, QRect viewport);
	void resizeViewport(int width, int height);
	void rotate(float increment, QVector3D rotation_axis);
	void translate(QVector3D translation);
	void translateX(float increment);
	void translateY(float increment);
	void translateZ(float increment);
	void zoom(float increment);
};