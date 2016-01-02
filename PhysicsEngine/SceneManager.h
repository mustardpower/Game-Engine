#pragma once
#include <vector>
#include <string>
#include <time.h>
#include <Windows.h>
#include "QuadTree.h"
#include "Renderable.h"
#include "Camera.h"
#include "PhysicsHandler.h"

//-----------------------------------------------------------------------------
// Name:		SceneManager
// Variables:	objects - vector of all objects within the world
//				quadtree - a quadtree data structure to minimize unneccessary updating of the screen
//				glCamera - a wrapper class for the camera data (positioning, focus point etc)
//				last_time_step - stores the time at each frame - the next frame uses this to calculate the time difference between frames
// Desc:		This class manages all the scene object data 
//-----------------------------------------------------------------------------
class SceneManager
{
private:
	std::vector<Renderable> objects;
	/*QuadTree quadtree;*/
	Camera glCamera;
	clock_t last_time_step;
public:
	SceneManager();

	std::vector<Renderable> getObjects();
	void addObject(Renderable object);
	void onMouseWheel(int nWheelNumber, int nDirection, int x, int y);
	void onLeftMouseDown(int x, int y);
	void onRightMouseDown(int x, int y);
	void onLeftMouseUp(int x, int y);
	void onRightMouseUp(int x, int y);
	void onKeyPress(int nKey);
	Camera getCamera();
	void update();
	void reset();

	bool toXML(std::string file_name);
	bool fromXML(std::string file_name);
};