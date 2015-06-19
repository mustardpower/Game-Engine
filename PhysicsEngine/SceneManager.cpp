#include "SceneManager.h"

SceneManager::SceneManager()
{
	objects = std::vector<Renderable>();
	objects.push_back(Renderable("cube",glm::vec3(10.0,0.0,0.0)));
	objects.push_back(Renderable("cube", glm::vec3(4.0, 0.0, 0.0)));
	/*objects.push_back(Renderable("cube", glm::vec3(0.0, 0.0, 0.0)));
	objects.push_back(Renderable("cube", glm::vec3(-4.0, 0.0, 0.0)));
	objects.push_back(Renderable("cube", glm::vec3(-10.0, 0.0, 0.0))); */
}
void SceneManager::update()
{
	// all physics handling here!!!
}
void SceneManager::onKeyPress(int nKey,char cAscii)
{
	if (cAscii == 43) // +
	{
	}
	else if (cAscii == 45) // -
	{
	}
	else if (nKey == GLUT_KEY_RIGHT)
	{ 
	}
	else if (nKey == GLUT_KEY_LEFT)
	{
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
std::vector<Renderable> SceneManager::getObjects()                 
{
	return objects;
}