//*****************************************************************************
// Application Class
//
//(c) 2003-2006 by Martin Christen. All Rights reserved.
//******************************************************************************/

#include "glApplication.h"

#include <GL/glew.h>
#include <GL/glut.h>

using namespace cwc;

std::list<glApplication*> glApplication::_gAppInstances;

//-----------------------------------------------------------------------------

glApplication::glApplication(void)
{
   _gAppInstances.push_back(this);

	#ifdef _DEBUG
		   ShowConsole();
	#endif
}

//-----------------------------------------------------------------------------

glApplication::~glApplication(void)
{
   // remove this instance from application list
   std::list<glApplication*>::iterator i = _gAppInstances.begin();
   
   while (i!=_gAppInstances.end())
   {
      if (*i == this)
      {
         _gAppInstances.erase(i);
         return;
      } 
      
      i++;   
   }
}

//-----------------------------------------------------------------------------

LRESULT glApplication::run(HINSTANCE hInstance)
{
   OnInit();
   LRESULT result = MainLoop(hInstance);
   OnExit();

   return result;
}

//-----------------------------------------------------------------------------

bool glApplication::MainLoop(HINSTANCE hInstance)
{
	MSG msg;
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAMEENGINE));
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
   return true;
}

//-----------------------------------------------------------------------------

void glApplication::ShowConsole()
{
	AllocConsole();

	// attach the new console to this application's process
	AttachConsole(GetCurrentProcessId());

	// reopen the std I/O streams to redirect I/O to the new console
	freopen("CON", "w", stdout);
	freopen("CON", "w", stderr);
	freopen("CON", "r", stdin);

	// use the console just like a normal one - printf(), getchar(), ...
}