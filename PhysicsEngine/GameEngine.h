#include <iostream>

#include <GL\glew.h>
#include <GL\glut.h>
#include <Windows.h>

#include "glutWindow.h"
#include "glsl.h"
#include "SceneManager.h"
#include "SceneRenderer.h"

class GameEngine : public cwc::glutWindow
{
protected:
   SceneManager sceneManager;
   SceneRenderer sceneRenderer;

public:
	GameEngine(char* GameEngineTitle) : cwc::glutWindow(GameEngineTitle){}

	virtual void OnRender(void);
	virtual void OnIdle();
	// When OnInit is called, a render context (in this case GLUT-GameEngine) 
	// is already available!
	virtual void OnInit();
	virtual void OnResize(int w, int h);
	virtual void OnClose(void);
	virtual void OnMouseDown(int button, int x, int y);    
	virtual void OnMouseUp(int button, int x, int y);
	virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y);
	virtual void OnKeyDown(int nKey, char cAscii);
	virtual void OnKeyUp(int nKey, char cAscii);
	virtual void OnPopupMenuSelection(int menuOption);
	virtual void OnMenuBarSelection(int menuOption);
	void initializeMenus();
	void initializeMenuBar();
	void initializeMouseMenus();

	/* No menu bar functionality in GLUT so implement this using WIN32 API */
	static void CALLBACK sMenuBarFunc(int menuOption);
};