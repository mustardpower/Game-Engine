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
void SceneManager::addObject(Renderable object)
{
	objects.push_back(object);
}
std::vector<Renderable> SceneManager::getObjects()                 
{
	return objects;
}