#include "SceneManager.h"

SceneManager::SceneManager()
{
	last_time_step = clock();
}
void SceneManager::update()
{
	clock_t current_time_step = clock();
	float dt = float(clock() - last_time_step) / CLOCKS_PER_SEC;
	
	for (std::vector<Renderable>::iterator object = objects.begin(); object != objects.end(); object++)
	{
		object->storeFrame();				// store the position, velocity, inertia etc
		object->updateFrame(dt);			// update the position based on the velocity etc
		if (collisionsDetected(*object))		
		{
			object->previousFrame();		// if the new position is in collision with another object
											// revert to previous position and use more accurate handling
		}
	}

	last_time_step = current_time_step;
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

bool SceneManager::collisionsDetected(Renderable obj)
{
	printf("collisionsDetected has not been implemented yet\n");
	return false;
}

int SceneManager::toXML(std::string file_name)
{
	tinyxml2::XMLDocument aDoc;
	tinyxml2::XMLDeclaration* decl = aDoc.NewDeclaration();
	aDoc.LinkEndChild(decl);

	tinyxml2::XMLNode* root = aDoc.NewElement("root");
	aDoc.LinkEndChild(root);

	// this may need modifying to deal with nested elements
	for (std::vector<Renderable>::iterator object = objects.begin(); object != objects.end(); object++)
	{
		object->serialize(aDoc, root);
	}

	tinyxml2::XMLError error = aDoc.SaveFile(file_name.c_str());
	if (error)
	{
		aDoc.PrintError();
		return error;
	}

	return error;
}

int SceneManager::fromXML(std::string file_name)
{
	Renderable scene_object;
	tinyxml2::XMLDocument aDoc;
	tinyxml2::XMLError error = aDoc.LoadFile(file_name.c_str());
	tinyxml2::XMLNode * pRoot = aDoc.FirstChild();
	if (pRoot == nullptr) return tinyxml2::XML_ERROR_FILE_READ_ERROR;
	tinyxml2::XMLNode * pRenderable = pRoot->NextSibling()->FirstChild();
	while (pRenderable != nullptr)
	{
		scene_object = Renderable::deserialize(pRenderable);
		objects.push_back(scene_object);
		pRenderable = pRenderable->NextSibling();
	}
	
	return error;
}