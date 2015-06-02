#include <fstream>
#include "glApplication.h"
#include "GameEngine.h"

using namespace std;

int main(int argc, char** argv)
{
	cwc::glApplication*  gameEngineApp = new cwc::glApplication;
	GameEngine* myWin = new GameEngine("The Game");

	gameEngineApp->run();
	delete gameEngineApp;

    return 0;
}