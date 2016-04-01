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
void SceneManager::onLeftMouseDown(int xPos, int yPos, int screen_width, int screen_height)
{
	glm::vec3 screenPos;
	glm::vec4 viewport = glm::vec4(0.0f, 0.0f, screen_width, screen_height);
	glm::mat4x4 modelView = glCamera.getViewMatrix() * glCamera.getModelMatrix();

	// calculate point on near plane
	screenPos = glm::vec3((float)xPos, (float)(screen_height - yPos), 0.0f);
	glm::vec3 worldPosNear = glm::unProject(screenPos, modelView, glCamera.getProjectionMatrix(), viewport);
	std::cout << "worldPosNear at: (" << worldPosNear.x << "," << worldPosNear.y << "," << worldPosNear.z << ")" << std::endl;

	// calculate point on far plane
	screenPos = glm::vec3((float)xPos, (float)(screen_height - yPos), 1.0f);
	glm::vec3 worldPosFar = glm::unProject(screenPos, modelView, glCamera.getProjectionMatrix(), viewport);
	std::cout << "worldPosFar at: (" << worldPosFar.x << "," << worldPosFar.y << "," << worldPosFar.z << ")" << std::endl;

	glm::vec3 ray_direction = glm::normalize(worldPosFar - worldPosNear);
	std::cout << "ray direction: (" << ray_direction.x << "," << ray_direction.y << "," << ray_direction.z << ")" << std::endl;
	for (std::vector<Renderable>::iterator object = objects.begin(); object != objects.end(); object++)
	{
		if (object->intersects(worldPosNear, ray_direction))
		{
			std::cout << "This object collides!!!!! CONGRATULATIONS" << std::endl;
		}
		else
		{
			std::cout << "This object does not collide!!!!!" << std::endl;
		}

		PhysicsHandler phyHandler;
		glm::vec3 ppoint(0.0, 0.0, -1.0);
		glm::vec3 pnormal(0.0, 0.0, -1.0);
		glm::vec3 collisionPoint = phyHandler.linePlaneCollisionPoint(worldPosNear, ray_direction, ppoint, pnormal);
		std::cout << "collision with plane at: (" << collisionPoint.x << "," << collisionPoint.y << "," << collisionPoint.z << ")" << std::endl;
	}
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
void SceneManager::onMouseWheel(int nWheelNumber, int nDirection, int window_width, int window_height)
{
	const int increment = 5;

	printf("window width: %d window height: %d\n", window_width, window_height);

	glm::vec3 screenPos;
	glm::vec4 viewport = glm::vec4(0.0f, 0.0f, window_width, window_height);
	glm::mat4x4 modelView = glCamera.getViewMatrix() * glCamera.getModelMatrix();

	// calculate point on near plane
	screenPos = glm::vec3((float)window_width / 2.0, (float)(window_height / 2.0), 0.0f);
	glm::vec3 worldPosNear = glm::unProject(screenPos, modelView, glCamera.getProjectionMatrix(), viewport);

	// calculate point on far plane
	screenPos = glm::vec3((float)window_width / 2.0, (float)(window_height / 2.0), 1.0f);
	glm::vec3 worldPosFar = glm::unProject(screenPos, modelView, glCamera.getProjectionMatrix(), viewport);

	glm::vec3 ray_direction = glm::normalize(worldPosFar - worldPosNear);

	if (nDirection > 0)
	{
		glCamera.translate(ray_direction);
	}
	if (nDirection < 0)
	{
		glCamera.translate(-ray_direction);
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

glm::vec3 SceneManager::viewportToNormalizedDeviceCoordinates(int xPos, int yPos, int screen_width, int screen_height)
{
	float x = (2.0f * xPos) / screen_width - 1.0f;
	float y = 1.0f - (2.0f * yPos) / screen_height;
	float z = 1.0f;
	return glm::vec3(x, y, z);
}

glm::vec2 SceneManager::normalizedDeviceCoordinatesToViewport(glm::vec3 ndc, int screen_width, int screen_height)
{
	float x = ((ndc.x + 1) * screen_width) / 2;
	float y = ((1.0f - ndc.y) * screen_height) / 2;
	return glm::vec2(x, y);
}