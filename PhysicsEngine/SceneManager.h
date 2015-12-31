#pragma once
#include <vector>
#include <string>
#include <Windows.h>
#include "QuadTree.h"
#include "Renderable.h"
#include "Camera.h"

//-----------------------------------------------------------------------------
// Name:		SceneManager
// Variables:	objects - vector of all objects within the world
//				quadtree - a quadtree data structure to minimize unneccessary updating of the screen
//				glCamera - a wrapper class for the camera data (positioning, focus point etc)
//				mouseLeftDown, mouseRightDown - stores mouse state
// Desc:		This class manages all the scene object data 
//-----------------------------------------------------------------------------
class SceneManager
{
private:
	std::vector<Renderable> objects;
	/*QuadTree quadtree;*/
	Camera glCamera;
	bool mouseLeftDown, mouseRightDown;
public:
	SceneManager();

	std::vector<Renderable> getObjects();
	void addObject(Renderable object);
	void onMouseDown(int button, int x, int y);
	void onMouseUp(int button, int x, int y);
	void onKeyPress(int nKey);
	Camera getCamera();
	void update();
	void reset();

	bool toXML(std::string file_name);
	bool fromXML(std::string file_name);
};