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
	QVector3D calculateLinearVelocity(QVector3D v, float jr, float m, QVector3D contactNormal);;
	void calculatePosition(QMatrix4x4 &modelmat, QVector3D velocity, float dt);
	float calculateReactionForce(QVector3D r1, QVector3D r2, QMatrix4x4 i1, QMatrix4x4 i2, float m1, float m2, float e, QVector3D contactNormal, QVector3D vr);
	QVector3D calculateRelativeVelocity(QVector3D v1, QVector3D v2, QVector3D w1, QVector3D w2, QVector3D r1, QVector3D r2);
	QVector3D totalMomentum(float mass1, QVector3D velocity1, float mass2, QVector3D velocity2);
	QVector3D linePlaneCollisionPoint(QVector3D lo, QVector3D ldir, QVector3D ppoint, QVector3D pnormal);
};