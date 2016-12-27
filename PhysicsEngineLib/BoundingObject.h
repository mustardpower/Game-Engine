#pragma once

class BoundingObject
{
public:
	virtual bool contains(QVector3D point) const = 0;
};