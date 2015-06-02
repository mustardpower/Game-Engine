#pragma once
#include <vector>
#include "QuadTree.h"
#include "Renderable.h"
#include "Camera.h"

//-----------------------------------------------------------------------------
// Name:		SceneManager
// Variables:	objects - vector of all objects within the world
//				quadtree - a quadtree data structure to minimize unneccessary updating of the screen
// Desc:		This class manages all the objects in the scene and ensures their properties are updated
//-----------------------------------------------------------------------------
class SceneManager
{
private:
	std::vector<Renderable> objects;
	QuadTree quadtree;
public:
	SceneManager();

	std::vector<Renderable> getObjects();
	void addObject(Renderable object);
	void update();
};