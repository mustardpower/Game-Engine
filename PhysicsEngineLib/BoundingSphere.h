#pragma once
#include "qvector3d.h"
#include "BoundingObject.h"

class BoundingSphere
{
private:
	float radius;
	QVector3D vecCentre;
	BoundingSphere();
	BoundingSphere(QVector3D min, QVector3D max);
	BoundingSphere(BoundingSphere& other);
	BoundingSphere& operator= (const BoundingSphere& other);

	bool contains(QVector3D point) const;
	bool intersects(const BoundingSphere& aBoundingSphere);
	bool intersects(QVector3D origin, QVector3D dir);
	float getRadius();
	QVector3D getCentre();
	void setDimensions(float aRadius, QVector3D centre);
};