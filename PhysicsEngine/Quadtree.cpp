#include "QuadTree.h"

QuadTree::QuadTree()
{
}

bool QuadTree::insert(GeoModel3D* anObject)
{
	// Ignore objects that do not belong in this quad tree

	AABB* objBoundingBox = anObject->getAABB();
	if (!boundary.intersects(objBoundingBox))
      return false; // object cannot be added

    // If there is space in this quad tree, add the object here
    if (objects.size() < QT_NODE_CAPACITY)
    {
	  objects.push_back(anObject);
      return true;
    }

    // Otherwise, subdivide and then add the point to whichever node will accept it
    if (northWest == nullptr)
      subdivide();

    if (northWest->insert(anObject)) return true;
    if (northEast->insert(anObject)) return true;
    if (southWest->insert(anObject)) return true;
    if (southEast->insert(anObject)) return true;

    // Otherwise, the point cannot be inserted for some unknown reason (this should never happen)
    return false;
}

void QuadTree::subdivide()
{
	northWest = new QuadTree();
	northEast = new QuadTree();
	southWest = new QuadTree();
	southEast = new QuadTree();
}

std::vector<GeoModel3D*> QuadTree::queryRange(AABB* range)
  {
    // Prepare an array of results
    std::vector<GeoModel3D*> objectsInRange;

    // Automatically abort if the range does not intersect this quad
    if (!boundary.intersects(range))
      return objectsInRange; // empty list

    // Check objects at this quad level
	for (unsigned int p = 0; p < objects.size(); p++)
    {
		if (range->intersects(objects[p]->getAABB()))
        objectsInRange.push_back(objects[p]);
    }

    // Terminate here, if there are no children
    if (northWest == nullptr)
      return objectsInRange;

    // Otherwise, add the points from the children
	objectsInRange.insert(objectsInRange.end(),northWest->queryRange(range).begin(),northWest->queryRange(range).end());
    objectsInRange.insert(objectsInRange.end(),northEast->queryRange(range).begin(),northEast->queryRange(range).end());
	objectsInRange.insert(objectsInRange.end(),southWest->queryRange(range).begin(),southWest->queryRange(range).end());
    objectsInRange.insert(objectsInRange.end(),southEast->queryRange(range).begin(),southEast->queryRange(range).end());

    return objectsInRange;
  }