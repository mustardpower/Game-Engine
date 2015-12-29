//*****************************************************************************
// Window Interface
//
//(c) 2003-2006 by Martin Christen. All Rights reserved.
//******************************************************************************/


#include "glWindow.h"

/*extern "C" 
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}*/

#include <iostream>

using namespace cwc;
using namespace std;

std::list<glWindow*> glWindow::_gWinInstances;

glWindow::glWindow()
{
	_gWindow = GetActiveWindow();
	_bScriptAttached = false;
}

glWindow::~glWindow()
{
}

bool glWindow::AttachScript(char* filename, bool bShowCompileErrors)
{
   return false;
}

HWND glWindow::getWindowHandle()
{
	return _gWindow;
}