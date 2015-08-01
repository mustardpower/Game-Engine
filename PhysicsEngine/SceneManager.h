#pragma once
#include <vector>
#include "QuadTree.h"
#include "Renderable.h"
#include "Camera.h"

//-----------------------------------------------------------------------------
// Name:		SceneManager
// Variables:	objects - vector of all objects within the world
//				quadtree - a quadtree data structure to minimize unneccessary updating of the screen
//				glCamera - a wrapper class for the camera data (positioning, focus point etc)
// Desc:		This class manages all the scene object data 
//-----------------------------------------------------------------------------
class SceneManager
{
private:
	std::vector<Renderable> objects;
	/*QuadTree quadtree;*/
	Camera glCamera;
public:
	SceneManager();

	std::vector<GeoModel3D*> getObjectModels();
	void addObject(Renderable object);
	void onKeyPress(int nKey, char cAscii);
	Camera getCamera();
	void update();
};