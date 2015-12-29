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
   
   int argc = 1;
   char* argv = "CWCApp";
   
   printf("glutInit");
   glutInit(&argc, &argv);
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