#pragma once
#include "qvector3d.h"
#include "BoundingObject.h"

using namespace std;

//-----------------------------------------------------------------------------
// Name:		AABB
// Variables:	vecMin - the minimum point in 3d space that the box is bounding
//				vecMax - the maximum point in 3d space that the box is bounding
// Desc:		Represents an axis aligned bounding box, note that there is no model matrix
//				as some transformations would cause the box to no longer be axis aligned
//-----------------------------------------------------------------------------
class AABB : public BoundingObject
{
private:
	QVector3D vecMin;	// in local coordinates
	QVector3D vecMax;	// in local coordinates
public:
	AABB();
	AABB(QVector3D min, QVector3D max);
	AABB(AABB& other);
	AABB& operator= (const AABB& other);

	bool contains(QVector3D point) const;
	bool intersects(const AABB& aBoundingBox);
	bool intersects(QVector3D origin, QVector3D dir);
	vector<unsigned int> getEdgeIndices();
	QVector3D getVecMin() const;
	QVector3D getVecMax() const;
	vector<float> getVertices();
	void setDimensions(QVector3D vMin, QVector3D vMax);
};