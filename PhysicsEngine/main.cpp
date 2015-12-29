#include <fstream>
#include "glApplication.h"
#include "GameEngine.h"
#include "resource.h"

using namespace std;

// GameEngine.cpp : Defines the entry point for the application.
//

// Global Variables:
HINSTANCE hInst;                                // current instance

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	cwc::glApplication*  gameEngineApp = new cwc::glApplication;
	GameEngine* myWin = new GameEngine("Game Engine");
	int result = gameEngineApp->run(hInstance);
	delete gameEngineApp;

	return result;
}