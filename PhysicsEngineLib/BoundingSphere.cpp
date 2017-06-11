#include "BoundingSphere.h"

BoundingSphere & BoundingSphere::operator=(const BoundingSphere & other)
{
	radius = other.radius;
	vecCentre = other.vecCentre;
	return *this;
}

bool BoundingSphere::contains(QVector3D point) const
{
	float distanceBetweenCentres = vecCentre.distanceToPoint(point);
	return distanceBetweenCentres < radius;
}

bool BoundingSphere::intersects(const BoundingSphere & aBoundingSphere)
{
	float distanceBetweenCentres = vecCentre.distanceToPoint(aBoundingSphere.vecCentre);
	return distanceBetweenCentres < radius + aBoundingSphere.radius;
}

bool BoundingSphere::intersects(QVector3D origin, QVector3D dir)
{
	// TO DO
	std::exception("Not Implemented");
	return false;
}

float BoundingSphere::getRadius()
{
	return radius;
}

QVector3D BoundingSphere::getCentre()
{
	return vecCentre;
}

void BoundingSphere::setDimensions(float aRadius, QVector3D centre)
{
	radius = aRadius;
	vecCentre = centre;
}
