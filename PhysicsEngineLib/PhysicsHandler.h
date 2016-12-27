#pragma once
#include "qmatrix4x4.h"
#include "qvector3d.h"

//-----------------------------------------------------------------------------
// Name:		PhysicsHandler
// Variables:	gravity - the magical constant that keeps us stuck to the floor
// Desc:		Used to calculate all interaction and geometry calculations
//				that impact on physical objects
//-----------------------------------------------------------------------------
class PhysicsHandler
{
private:
	static const QVector3D gravity;	// in N/kg
public:
	void calculatePosition(QMatrix4x4 &modelmat, QVector3D velocity, float dt);
	QVector3D totalMomentum(float mass1, QVector3D velocity1, float mass2, QVector3D velocity2);
	QVector3D linePlaneCollisionPoint(QVector3D lo, QVector3D ldir, QVector3D ppoint, QVector3D pnormal);
};