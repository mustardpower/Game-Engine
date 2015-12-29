//*****************************************************************************
// Application Class
//
//(c) 2003-2006 by Martin Christen. All Rights reserved.
//******************************************************************************/

#ifndef GL_APPLICATION_H
#define GL_APPLICATION_H

//! \defgroup app Application
#include <list>
#include <Windows.h>
#include "Resource.h"

namespace cwc
{
   //! \ingroup app
   class glApplication
   {
   public:
      glApplication(void);
      virtual ~glApplication(void);
      
      //! OnInit is called when application starts. This is for example a good place to create (main) windows.
      virtual void OnInit() {};
      
      //! OnExit is called when application terminates.
      virtual void OnExit() {};
      
      //! Return Name of Application or 0 if undefined.
      char* GetAppName(){return 0;}
      
      //! Set Name of Application
      void SetAppName(char* sAppName);
      
      //! Starts Application - Contains windows message loop
	  LRESULT run(HINSTANCE hInstance);

	  bool MainLoop(HINSTANCE hInstance);
      
      //! ShowConsole is for Windows only: Show a console where cout/printf etc are redirected. This should not be used
      // for productive applications, but is "nice to have" when developing certain small applications.
      void ShowConsole();
      
   protected:
      static std::list<glApplication*> _gAppInstances;  
   };
}

#endif