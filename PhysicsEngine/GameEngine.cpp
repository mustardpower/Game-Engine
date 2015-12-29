#include "GameEngine.h"
#include "SceneManager.h"
#include "tiny_obj_loader.h"

	// When OnInit is called, a render context (in this case GLUT-GameEngine) 
	// is already available!
	void GameEngine::OnInit()
	{
		initializeMenu();
		sceneRenderer.onInit();
		GeoModel3D* cube = new GeoModel3D("cube");	// load the model from the file name
		sceneRenderer.createVAO(cube);				// upload model data to graphics card
		sceneManager.addObject(Renderable(cube, glm::vec3(10, 0.0, 0.0)));	//add an instance of a renderable object with that data
	}

	void GameEngine::OnRender(void)
{
	std::vector<GeoModel3D*> object_models;
	std::vector<Renderable> objects = sceneManager.getObjects();
	Camera camera = sceneManager.getCamera();
	sceneManager.update();
	sceneRenderer.renderScene(camera,objects);
}

	void GameEngine::OnIdle() { }

	void GameEngine::OnResize(int w, int h) {}
	void GameEngine::OnClose(void)
	{
	}
	void GameEngine::OnMouseDown(int button, int x, int y) 
	{
		sceneManager.onMouseDown(button, x, y);
		glutPostRedisplay();
	}    
	void GameEngine::OnMouseUp(int button, int x, int y) 
	{
		sceneManager.onMouseUp(button, x, y);
		glutPostRedisplay();
	}
	void GameEngine::OnMouseWheel(int nWheelNumber, int nDirection, int x, int y){}
	void GameEngine::OnKeyDown(int nKey, char cAscii)
	{       
		if (cAscii == 27) // 0x1b = ESC
		{
			this->Close(); // Close GameEngine!
		}
		else
		{
			sceneManager.onKeyPress(nKey,cAscii);
		}

		glutPostRedisplay();
	};
	void GameEngine::OnKeyUp(int nKey, char cAscii)
	{
		if (cAscii == 'f')
		{
			SetFullscreen(true);
		}
		else if (cAscii == 'w')
		{
			SetFullscreen(false);
		}
	};

	void GameEngine::OnMenuSelection(int menuOption)
	{
		switch (menuOption)
		{
		case 1:
			glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
			break;
		case 2:
			glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
			break;
		case 3:
			glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
			break;
		case 4:
			glClearColor(1.0f, 0.5f, 0.0f, 0.0f);
			break;
		default:
			glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
			break;
		}

		glutPostRedisplay();
	}

	void GameEngine::initializeMenu()
	{
		//add menu entries with their ID
		glutAddMenuEntry("Red", 1);
		glutAddMenuEntry("Blue", 2);
		glutAddMenuEntry("Green", 3);
		glutAddMenuEntry("Orange", 4);

		// attach the menu to the right mouse button
		glutAttachMenu(GLUT_RIGHT_BUTTON);
	}