#include "AABB.h"
#include <algorithm>

using namespace std;

AABB::AABB()
{
	vecMin = QVector3D(-1.0, -1.0, -1.0);
	vecMax = QVector3D(1.0, 1.0, 1.0);
}
AABB::AABB(QVector3D a, QVector3D b)
{
	vecMin = a;
	vecMax = b;
}
bool AABB::contains(QVector3D point) const
{
	// check point x,y,z values are within the axis-aligned bounding box - return true if they are, false if not
	if((point.x() >= vecMin.x() && point.x() <= vecMax.x())
		&&(point.y() >= vecMin.y() && point.y() <= vecMax.y())
		&&(point.z() >= vecMin.z() && point.z() <= vecMax.z()))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool AABB::intersects(const AABB& aBoundingBox)
{
	return aBoundingBox.contains(vecMin) || aBoundingBox.contains(vecMax);
}

bool AABB::intersects(QVector3D origin, QVector3D dir)
{
	QVector3D dirfrac(1.0f / dir.x(), 1.0f / dir.y(), 1.0f / dir.z());
	
	float t1 = (vecMin.x() - origin.x())*dirfrac.x();
	float t2 = (vecMax.x() - origin.x())*dirfrac.x();
	float t3 = (vecMin.y() - origin.y())*dirfrac.y();
	float t4 = (vecMax.y() - origin.y())*dirfrac.y();
	float t5 = (vecMin.z() - origin.z())*dirfrac.z();
	float t6 = (vecMax.z() - origin.z())*dirfrac.z();

	float tmin = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
	float tmax = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but whole AABB is behind us
	if (tmax < 0)
	{
		return false;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax)
	{
		return false;
	}

	return true;
}

QVector3D AABB::getVecMin()
{
	return vecMin;
}

QVector3D AABB::getVecMax()
{
	return vecMax;
}
