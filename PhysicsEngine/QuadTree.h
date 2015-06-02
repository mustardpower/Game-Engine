#include "AABB.h"
#include <vector>
#include "GeoModel3D.h"

class QuadTree
{
private:
	// Arbitrary constant to indicate how many elements can be stored in this quad tree node
  static const unsigned int QT_NODE_CAPACITY = 4;

  // Axis-aligned bounding box stored as a center with half-dimensions
  // to represent the boundaries of this quad tree
  AABB boundary;

  // Objects in this quad tree node
  std::vector<GeoModel3D*> objects;

  // Children
  QuadTree* northWest;
  QuadTree* northEast;
  QuadTree* southWest;
  QuadTree* southEast;

public:
  // Methods
  QuadTree();
  bool insert(GeoModel3D* anObject);				// true if successfully added, false if not possible
  void subdivide(); // create four children that fully divide this quad into four quads of equal area
  std::vector<GeoModel3D*> queryRange(AABB* range);
};