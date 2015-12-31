#include "SceneManager.h"

SceneManager::SceneManager()
{
	mouseLeftDown = false;
	mouseRightDown = false;
}
void SceneManager::update()
{
	const int increment = 1.0;
	glm::vec3 rotation_axis = glm::vec3(0.0, 1.0, 0.0);

	if (mouseLeftDown)
	{
		glCamera.rotate(increment, rotation_axis);
		glutPostRedisplay();
	}
	if (mouseRightDown)
	{
		glCamera.rotate(-increment, rotation_axis);
		glutPostRedisplay();
	}

	// ALL PHYSICS HANDLING HERE!!!
}

void SceneManager::reset()
{
	objects.clear();
}
void SceneManager::onMouseDown(int button, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		mouseLeftDown = true;
	}
	if (button == GLUT_RIGHT_BUTTON)
	{
		mouseRightDown = true;
	}
}

void SceneManager::onMouseUp(int button, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		mouseLeftDown = false;
	}
	if (button == GLUT_RIGHT_BUTTON)
	{
		mouseRightDown = false;
	}
}
void SceneManager::onKeyPress(int nKey,char cAscii)
{
	const int increment = 1;

	if (nKey == GLUT_KEY_RIGHT)
	{ 
		glCamera.translateX(increment);
	}
	else if (nKey == GLUT_KEY_LEFT)
	{
		glCamera.translateX(-increment);
	}
	else if (nKey == GLUT_KEY_UP)
	{
		glCamera.translateY(increment);
	}
	else if (nKey == GLUT_KEY_DOWN)
	{
		glCamera.translateY(-increment);
	}
	else
	{
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