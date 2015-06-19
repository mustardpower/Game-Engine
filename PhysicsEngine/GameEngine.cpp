#include "GameEngine.h"
#include "SceneManager.h"
#include "tiny_obj_loader.h"

void GameEngine::OnRender(void)
{
	std::vector<Renderable> objects;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	sceneManager.update();
    if (shader) shader->begin();
	objects = sceneManager.getObjects();
	for(std::vector<Renderable>::iterator it = objects.begin(); it != objects.end(); it++)
	{
		it->render(shader);
	}

    if (shader) shader->end();
    glutSwapBuffers();
}

	void GameEngine::OnIdle() { }

	// When OnInit is called, a render context (in this case GLUT-GameEngine) 
	// is already available!
	void GameEngine::OnInit()
	{
		glClearColor(0.5f, 0.5f, 1.0f, 0.0f);
		glEnable(GL_DEPTH_TEST);
		glShadeModel(GL_SMOOTH);

		glClearDepth( 1.0f );
		glDepthFunc( GL_LEQUAL );	

		shader = SM.loadfromFile("vert_shader.vs","frag_shader.fs"); // load (and compile, link) shaders from file
		  if (shader==0) 
			  std::cout << "Error Loading, compiling or linking shader\n";

		glGenBuffers(1,&VBO);	//create a vertex buffer object for vertices, normals and texture coordinates
		glBindBuffer(GL_ARRAY_BUFFER, VBO); //bind the buffer

	}

	void GameEngine::OnResize(int w, int h) {}
	void GameEngine::OnClose(void)
	{
		glDeleteBuffers(1, &VBO);
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