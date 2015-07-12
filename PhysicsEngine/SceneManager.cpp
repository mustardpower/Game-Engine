#include "SceneManager.h"

SceneManager::SceneManager()
{
}
void SceneManager::update()
{
	// all physics handling here!!!
}
void SceneManager::onKeyPress(int nKey,char cAscii)
{
	const int increment = 1;

	if (cAscii == 43) // +
	{
		glCamera.rotate(increment);
	}
	else if (cAscii == 45) // -
	{
		glCamera.rotate(-increment);
	}
	else if (nKey == GLUT_KEY_RIGHT)
	{ 
		glCamera.translateX(increment);
	}
	else if (nKey == GLUT_KEY_LEFT)
	{
		glCamera.translateX(-increment);
	}
	else if (nKey == GLUT_KEY_UP)
	{
	}
	else if (nKey == GLUT_KEY_DOWN)
	{
	}
	else if (cAscii == 97) // a
	{
	}
	else if (cAscii == 100) // d
	{
	}
	else
	{
		printf("The key has no action in the scene\n");
	}
}
void SceneManager::addObject(Renderable object)
{
	objects.push_back(object);
}
std::vector<GeoModel3D*> SceneManager::getObjectModels()                 
{
	std::vector<Renderable>::iterator object;
	std::vector<GeoModel3D*> object_models;
	for(object = objects.begin();object != objects.end(); object++)
	{
		GeoModel3D* model = object->getModel();
		object_models.push_back(object->getModel());
	}
	return object_models;
}
Camera SceneManager::getCamera()
{
	return glCamera;
}