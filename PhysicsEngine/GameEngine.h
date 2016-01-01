#include <iostream>
#include <Windows.h>
#include <windowsx.h>

#include "glWindow.h"
#include "glsl.h"
#include "SceneManager.h"
#include "SceneRenderer.h"

class GameEngine : public cwc::glWindow
{
private:
	static HINSTANCE hInstance;
	WNDCLASSEXW wcex;
	SceneManager sceneManager;
	SceneRenderer sceneRenderer;

public:
	GameEngine(char* GameEngineTitle);
	ATOM RegisterClass(HINSTANCE hInstance);

	virtual void OnRender(void);
	virtual void OnIdle();
	// When OnInit is called, a render context (in this case GLUT-GameEngine) 
	// is already available!
	virtual void OnInit();
	virtual void OnResize(int w, int h);
	virtual void OnClose(void);
	virtual void OnLeftMouseDown(int x, int y); 
	virtual void OnRightMouseDown(int x, int y);
	virtual void OnLeftMouseUp(int x, int y);
	virtual void OnRightMouseUp(int x, int y);
	virtual void OnMouseWheel(int nWheelNumber, int nDirection, int x, int y);
	virtual void OnMouseMove(int x, int y);
	virtual void OnLeftMouseDrag(int x, int y);
	virtual void OnKeyDown(int nKey, char cAscii);
	virtual void OnKeyUp(int nKey, char cAscii);
	virtual void OnPopupMenuSelection(int menuOption);
	virtual void OnEngineReset();
	virtual void OnXMLLoad();
	virtual void OnXMLSave();

	// Commands:
	virtual void Repaint(); //! Queue repaint of window
	virtual void Update(); //! Force immediate repaint
	virtual void  SetFullscreen(bool bFullscreen); //! Sets window to fullscreen or windowed mode.
	virtual void Hide(); //! Hide the window
	virtual void Show(); //! Show the window
	virtual void Close();

	void initializeMenuBar();

	static void CALLBACK sMenuBarFunc(int menuOption);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static INT_PTR CALLBACK GameEngine::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT handleWindowsMessage(cwc::glWindow* window, UINT message, WPARAM wParam, LPARAM lParam);
};