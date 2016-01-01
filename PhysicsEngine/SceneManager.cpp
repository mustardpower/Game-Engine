#include "SceneManager.h"

SceneManager::SceneManager()
{
}
void SceneManager::update()
{
	physicsHandler.updateFrame();
}

void SceneManager::reset()
{
	objects.clear();
}
void SceneManager::onLeftMouseDown(int x, int y)
{
	const float increment = 1.0f;
	glm::vec3 rotation_axis = glm::vec3(0.0, 1.0, 0.0);
	glCamera.rotate(increment, rotation_axis);
}

void SceneManager::onRightMouseDown(int x, int y)
{
	const int increment = 1.0;
	glm::vec3 rotation_axis = glm::vec3(0.0, 1.0, 0.0);
	glCamera.rotate(-increment, rotation_axis);
}

void SceneManager::onLeftMouseUp(int x, int y)
{
}

void SceneManager::onRightMouseUp(int x, int y)
{
}
void SceneManager::onMouseWheel(int nWheelNumber, int nDirection, int x, int y)
{
	const int increment = 5;
	glm::vec3 translation_vec(0.0, 0.0, increment);
	if (nDirection > 0)
	{
		glCamera.translate(translation_vec);
	}
	if (nDirection < 0)
	{
		glCamera.translate(-translation_vec);
	}
}
void SceneManager::onKeyPress(int nKey)
{
	const int increment = 1;

	switch (nKey)
	{
	case VK_LEFT:
		glCamera.translateX(-increment);
		break;
	case VK_RIGHT:
		glCamera.translateX(increment);
		break;
	case VK_UP:
		glCamera.translateY(increment);
		break;
	case VK_DOWN:
		glCamera.translateY(-increment);
		break;
	default:
		glCamera.translateZ(-increment);
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
Camera SceneManager::getCamera()
{
	return glCamera;
}

bool SceneManager::toXML(std::string file_name)
{
	return false;
}

bool SceneManager::fromXML(std::string file_name)
{
	return false;
}