#include <iostream>
#include <Windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include <chrono>

#include "glWindow.h"
#include "glsl.h"
#include "SceneRenderer.h"
#include "UnitsManager.h"

enum mode { PAN, ZOOM, SELECTION, ROTATE };

class GameEngine : public cwc::glWindow
{
private:
	static HINSTANCE hInstance;
	HIMAGELIST hImageList;
	WNDCLASSEXW wcex;
	SceneRenderer sceneRenderer;
	static std::string applicationDirectory;
	static std::string modelDirectory;
	static std::string texturesDirectory;
	std::vector<Renderable> objects;
	Camera glCamera;
	std::chrono::steady_clock::time_point last_time_step;
	static UnitsManager unitManager;
	mode viewMode;
	glm::vec2 lastMousePos;

public:
	GameEngine(char* GameEngineTitle);
	ATOM RegisterWindow(HINSTANCE hInstance);
	static std::string getApplicationDirectory();
	static std::string getModelDirectory();
	static std::string getTexturesDirectory();

	void clearSelection();
	bool collisionsDetected(Renderable obj);

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
	virtual void OnMouseWheel(int nWheelNumber, int nDirection);
	virtual void OnLeftMouseDrag(int x, int y, DWORD flags);
	virtual void OnMouseMove(int x, int y);
	virtual void OnKeyDown(int nKey, char cAscii);
	virtual void OnKeyUp(int nKey, char cAscii);
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

	int LoadFromFile(std::string file_name);
	int SaveToFile(std::string file_name);

	HWND createSimpleToolbar(HWND hWndParent);
	void initializeMenuBar();
	void getClientAreaSize(int& width, int& height);

	virtual void OnSelectionModeSelected();
	virtual void OnRotateModeSelected();
	virtual void OnPanModeSelected();
	virtual void OnZoomModeSelected();

	static void CALLBACK sMenuBarFunc(int menuOption);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	static INT_PTR CALLBACK GameEngine::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT handleWindowsMessage(cwc::glWindow* window, UINT message, WPARAM wParam, LPARAM lParam);
};