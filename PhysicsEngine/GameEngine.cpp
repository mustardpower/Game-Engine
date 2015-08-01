#include "GameEngine.h"
#include "SceneManager.h"
#include "tiny_obj_loader.h"

void GameEngine::OnRender(void)
{
	std::vector<GeoModel3D*> object_models;
	std::vector<Renderable> objects = sceneManager.getObjects();
	Camera camera = sceneManager.getCamera();
	sceneManager.update();
	sceneRenderer.renderScene(camera,objects);
}

	void GameEngine::OnIdle() { }

	// When OnInit is called, a render context (in this case GLUT-GameEngine) 
	// is already available!
	void GameEngine::OnInit()
	{
		sceneRenderer.onInit();
		GeoModel3D* cube = new GeoModel3D("cube");	// load the model from the file name
		sceneRenderer.createVAO(cube);				// upload model data to graphics card
		sceneManager.addObject(Renderable(cube, glm::vec3(10, 0.0, 0.0)));	//add an instance of a renderable object with that data
		sceneManager.addObject(Renderable(cube, glm::vec3(20, 0.0, 0.0)));	//add an instance of a renderable object with that data
	}

	void GameEngine::OnResize(int w, int h) {}
	void GameEngine::OnClose(void)
	{
	}
	void GameEngine::OnMouseDown(int button, int x, int y) {}    
	void GameEngine::OnMouseUp(int button, int x, int y) {}
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