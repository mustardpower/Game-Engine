#include "AABB.h"
#include <algorithm>
#include <qdebug.h>

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

AABB::AABB(AABB& other)
{
	vecMin = other.vecMin;
	vecMax = other.vecMax;
}
AABB & AABB::operator=(const AABB & other)
{
	vecMin = other.vecMin;
	vecMax = other.vecMax;
	return *this;
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

QVector3D AABB::getCenter() const 
{
	return (vecMax - vecMin) / 2;
}

vector<unsigned int> AABB::getEdgeIndices()
{
	std::vector<unsigned int> indices = {
		0,1,  1,5,  5,4,  4,0,    // edges of the top face
		7,3,  3,2,  2,6,  6,7,    // edges of the bottom face
		1,2,  0,3,  4,7,  5,6	 // edges connecting top face to bottom face
	};

	return indices;
}

QVector3D AABB::getVecMin() const
{
	return vecMin;
}

QVector3D AABB::getVecMax() const
{
	return vecMax;
}

vector<float> AABB::getVertices()
{
	QVector3D min = getVecMin();
	QVector3D max = getVecMax();
	std::vector<float> vertices = {
		max.x(),  max.y(),  max.z(), // Vertex 0 (X, Y, Z)
		max.x(),  max.y(),  min.z(), // Vertex 1 (X, Y, Z)
		max.x(),	min.y(),  min.z(), // Vertex 2 (X, Y, Z)
		max.x(),	min.y(),  max.z(), // Vertex 3 (X, Y, Z)
		min.x(),  max.y(), max.z(), // Vertex 4 (X, Y, Z)
		min.x(),  max.y(), min.z(), // Vertex 5 (X, Y, Z)
		min.x(),	min.y(), min.z(), // Vertex 6 (X, Y, Z)
		min.x(),	min.y(), max.z()  // Vertex 7 (X, Y, Z)
	};
	return vertices;
}

QVector3D AABB::overlap(AABB anotherBox)
{
	float overlapX = std::max(0.0f, min(vecMax.x(), anotherBox.vecMax.x()) - max(vecMin.x(), anotherBox.vecMin.x()));
	float overlapY = std::max(0.0f, min(vecMax.y(), anotherBox.vecMax.y()) - max(vecMin.y(), anotherBox.vecMin.y()));
	float overlapZ = std::max(0.0f, min(vecMax.z(), anotherBox.vecMax.z()) - max(vecMin.z(), anotherBox.vecMin.z()));
	return QVector3D(overlapX, overlapY, overlapZ);
}

void AABB::setDimensions(QVector3D vMin, QVector3D vMax)
{
	vecMin = vMin;
	vecMax = vMax;
}
