#include "GameEngine.h"
#include "tiny_obj_loader.h"
#include "resource.h"

#include <string>

	// When OnInit is called, a render context (in this case GLUT-GameEngine) 
	// is already available!

	#define MAX_LOADSTRING 100
	WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
	WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

	HINSTANCE GameEngine::hInstance;
	std::string GameEngine::applicationDirectory = GameEngine::getApplicationDirectory();
	std::string GameEngine::modelDirectory = GameEngine::getModelDirectory();
	std::string GameEngine::texturesDirectory = GameEngine::getTexturesDirectory();

	GameEngine::GameEngine(char* GameEngineTitle) : cwc::glWindow()
	{
		OnInit();
	}

	void GameEngine::clearSelection()
	{
		for (std::vector<Renderable>::iterator object = objects.begin(); object != objects.end(); object++)
		{
			object->setSelection(false);
		}
	}

	//
	//  FUNCTION: MyRegisterClass()
	//
	//  PURPOSE: Registers the window class.
	//
	ATOM GameEngine::RegisterWindow(HINSTANCE hInstance)
	{
		LoadStringW(hInstance, IDC_GAMEENGINE, szWindowClass, MAX_LOADSTRING);
		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = GameEngine::WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = LoadIconW(hInstance, MAKEINTRESOURCEW(IDI_GAMEENGINE));
		wcex.hCursor = LoadCursorW(nullptr, MAKEINTRESOURCEW(IDC_ARROW));
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = szWindowClass;
		wcex.hIconSm = (HICON)LoadImageW(hInstance, // small class icon 
			MAKEINTRESOURCEW(IDI_SMALL),
			IMAGE_ICON,
			GetSystemMetrics(SM_CXSMICON),
			GetSystemMetrics(SM_CYSMICON),
			LR_DEFAULTCOLOR);
		return RegisterClassExW(&wcex);
	}

	std::string GameEngine::getApplicationDirectory()
	{
		if (applicationDirectory.empty())
		{
			TCHAR pathBuffer[MAX_PATH];
			GetCurrentDirectory(MAX_PATH, pathBuffer);
			applicationDirectory = std::string(pathBuffer);
		}
		return applicationDirectory;
	}

	std::string GameEngine::getModelDirectory()
	{
		return getApplicationDirectory() + "\\models\\";
	}

	std::string GameEngine::getTexturesDirectory()
	{
		return getApplicationDirectory() + "\\textures\\";
	}

	void GameEngine::OnInit()
	{
		// Ensure that the common control DLL is loaded, and then create 
		// the header control. 
		INITCOMMONCONTROLSEX icex;  //declare an INITCOMMONCONTROLSEX Structure
		icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
		icex.dwICC = ICC_BAR_CLASSES;   //set dwICC member to ICC_LISTVIEW_CLASSES    
											 // this loads list-view and header control classes.
		InitCommonControlsEx(&icex);

		_gWinInstances.push_back(this);

		LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
		wcex.cbSize = sizeof(WNDCLASSEX);

		hInstance = GetModuleHandle(NULL); // Store instance handle in our global variable
		RegisterWindow(hInstance);
		_gWindow = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
		Show();

		createSimpleToolbar(_gWindow);
		sceneRenderer.onInit(_gWindow);

		SetTimer(_gWindow,             // handle to main window 
			IDT_TIMER1,            // timer identifier 
			16,                 // approx 60 fps
			(TIMERPROC)NULL);     // no timer callback
	}

	void GameEngine::OnRender()
	{ 
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(_gWindow, &ps);
		std::vector<GeoModel3D*> object_models;
		sceneRenderer.renderScene(hdc,glCamera,objects);
		EndPaint(_gWindow, &ps);
	}

	void GameEngine::OnIdle() { }

	void GameEngine::OnResize(int w, int h) {}
	void GameEngine::OnClose(void)
	{
		DestroyWindow(_gWindow);
		PostQuitMessage(0);
	}
	void GameEngine::OnLeftMouseDown(int x, int y) 
	{
		glCamera.onLeftMouseDown(x, y);
	}  
	void GameEngine::OnRightMouseDown(int x, int y)
	{
		HMENU hmenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));
		if (hmenu == NULL) return;
		POINT pt = { x,y };
		ClientToScreen(_gWindow, &pt);
		HMENU hPopupMenu = GetSubMenu(hmenu, 0);
		TrackPopupMenu(hPopupMenu, TPM_BOTTOMALIGN | TPM_LEFTALIGN, pt.x,pt.y, 0, _gWindow, NULL);
	}
	void GameEngine::OnLeftMouseUp(int xPos, int yPos) 
	{
		int screen_width = 0;
		int screen_height = 0;
		getClientAreaSize(screen_width, screen_height);
		glm::vec4 viewport = glm::vec4(0.0f, 0.0f, screen_width, screen_height);

		// calculate point on near and far plane
		glm::vec3 worldPosNear = glCamera.pointOnNearPlane(xPos, screen_height - yPos, viewport);
		glm::vec3 worldPosFar = glCamera.pointOnFarPlane(xPos, screen_height - yPos, viewport);

		glm::vec3 ray_direction = glm::normalize(worldPosFar - worldPosNear);
		for (std::vector<Renderable>::iterator object = objects.begin(); object != objects.end(); object++)
		{
			if (object->intersects(worldPosNear, ray_direction))
			{
				object->setSelection(true);
			}
			else
			{
				object->setSelection(false);
			}
		}
	}

	void GameEngine::getClientAreaSize(int& screen_width, int& screen_height)
	{
		RECT windowRect;
		GetClientRect(_gWindow, &windowRect);
		screen_width = windowRect.right - windowRect.left;
		screen_height = windowRect.bottom - windowRect.top;
	}
	void GameEngine::OnRightMouseUp(int x, int y)
	{
		clearSelection();
	}
	void GameEngine::OnMouseWheel(int nWheelNumber, int nDirection)
	{
		int screen_width = 0;
		int screen_height = 0;
		getClientAreaSize(screen_width, screen_height);
		const int increment = 5;

		glm::vec4 viewport = glm::vec4(0.0f, 0.0f, screen_width, screen_height);

		// calculate point on near and far plane
		glm::vec3 worldPosNear = glCamera.pointOnNearPlane(screen_width / 2.0, screen_height / 2.0, viewport);
		glm::vec3 worldPosFar = glCamera.pointOnFarPlane(screen_width / 2.0, screen_height / 2.0, viewport);
		glm::vec3 ray_direction = glm::normalize(worldPosFar - worldPosNear);

		if (nDirection > 0)
		{
			glCamera.translate(ray_direction);
		}
		if (nDirection < 0)
		{
			glCamera.translate(-ray_direction);
		}
	}

	void GameEngine::OnMouseMove(int x, int y)
	{

	}

	void GameEngine::OnKeyDown(int nKey, char cAscii)
	{       
		if (cAscii == 27) // 0x1b = ESC
		{
			this->Close(); // Close GameEngine!
		}
		else
		{
			const int increment = 1;

			switch (nKey)
			{
			case VK_LEFT:
				glCamera.translateX(-increment);
				break;
			case VK_RIGHT:
				glCamera.translateX(increment);
				break;
			case VK_UP:
				glCamera.translateY(increment);
				break;
			case VK_DOWN:
				glCamera.translateY(-increment);
				break;
			default:
				glCamera.translateZ(-increment);
			}
		}
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

	void GameEngine::OnPopupMenuSelection(int menuOption)
	{
		
	}

	void GameEngine::OnRotateModeSelected()
	{
		glCamera.setCameraMode(CAMERA_ROTATE);
	}

	void GameEngine::OnPanModeSelected()
	{
		glCamera.setCameraMode(CAMERA_PAN);
	}

	void GameEngine::OnZoomModeSelected()
	{
		glCamera.setCameraMode(CAMERA_ZOOM);
	}

	void GameEngine::initializeMenuBar()
	{
		HWND hwnd = GetActiveWindow();
		HMENU hMenu = LoadMenu(NULL, MAKEINTRESOURCE(IDC_GAMEENGINE));
		SetMenu(hwnd, hMenu);
	}

	void GameEngine::sMenuBarFunc(int menuOption)
	{
		HWND CurrentWindow = GetActiveWindow();
		std::list<glWindow*>::iterator i = _gWinInstances.begin();

		while (i != _gWinInstances.end())
		{
			if ((*i)->getWindowHandle() == CurrentWindow)
			{
				(*i)->OnMenuBarSelection(menuOption);
			}

			i++;
		}
	}

	void  GameEngine::SetFullscreen(bool bFullscreen)
	{
	}

	void GameEngine::OnLeftMouseDrag(int x, int y, DWORD flags)
	{
		if (flags & MK_LBUTTON)
		{
			int screen_width = 0;
			int screen_height = 0;
			getClientAreaSize(screen_width, screen_height);
			glCamera.onLeftMouseDrag(x, y, screen_width, screen_height);
		}
	}

	void GameEngine::OnXMLLoad()
	{
		wchar_t buffer[MAX_PATH] = L"";
		OPENFILENAMEW ofn = { 0 };  

		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = _gWindow;
		ofn.lpstrFilter = L"XMLFiles\0*.xml\0TextFiles\0*.txt\0All Files\0*.*\0";
		ofn.nFilterIndex = 1; // for some reason this is 1-based not zero-based.

		ofn.Flags = OFN_FILEMUSTEXIST;  // only allow the user to open files that actually exist
		ofn.lpstrFile = buffer;
		ofn.nMaxFile = MAX_PATH;  // size of our 'buffer' buffer

								  // Now that we've prepped the struct, actually open the dialog:
								  //  the below function call actually opens the "File Open" dialog box, and returns
								  //  once the user exits out of it

		if (GetOpenFileNameW(&ofn))
		{
			// code reaches here if the user hit 'OK'.  The full path of the file
			//  they selected is now stored in 'buffer'
			std::wstring ws(buffer);
			std::string file_name(ws.begin(), ws.end());
			Renderable scene_object;
			tinyxml2::XMLDocument aDoc;
			tinyxml2::XMLError error = aDoc.LoadFile(file_name.c_str());
			tinyxml2::XMLNode * pRoot = aDoc.FirstChild();
			if (pRoot != nullptr)
			{
				tinyxml2::XMLNode * pRenderable = pRoot->NextSibling()->FirstChild();
				while (pRenderable != nullptr)
				{
					error = Renderable::deserialize(pRenderable, scene_object);
					if (error == tinyxml2::XML_SUCCESS)
					{
						objects.push_back(scene_object);
					}
					pRenderable = pRenderable->NextSibling();
				}
			}

			if (error)
			{
				MessageBoxW(_gWindow, L"Could not load XML", L"Error loading XML", MB_OK);
			}
		}
	}

	void GameEngine::OnXMLSave()
	{
		wchar_t buffer[MAX_PATH] = L"";
		OPENFILENAMEW ofn = { 0 };

		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = _gWindow;
		ofn.lpstrFilter = L"XMLFiles\0*.xml\0TextFiles\0*.txt\0";
		ofn.nFilterIndex = 1; // for some reason this is 1-based not zero-based.

		ofn.Flags = NULL; 
		ofn.lpstrFile = buffer;
		ofn.nMaxFile = MAX_PATH;  // size of our 'buffer' buffer

								  // Now that we've prepped the struct, actually open the dialog:
								  //  the below function call actually opens the "File Save" dialog box, and returns
								  //  once the user exits out of it

		if (GetSaveFileNameW(&ofn))
		{
			// code reaches here if the user hit 'OK'.  The full path of the file
			//  they selected is now stored in 'buffer'
			std::wstring ws(buffer);
			std::string file_name(ws.begin(), ws.end());
			tinyxml2::XMLDocument aDoc;
			tinyxml2::XMLDeclaration* decl = aDoc.NewDeclaration();
			aDoc.LinkEndChild(decl);

			tinyxml2::XMLNode* root = aDoc.NewElement("root");
			aDoc.LinkEndChild(root);

			// this may need modifying to deal with nested elements
			for (std::vector<Renderable>::iterator object = objects.begin(); object != objects.end(); object++)
			{
				object->serialize(aDoc, root);
			}

			tinyxml2::XMLError error = aDoc.SaveFile(file_name.c_str());
			if (error)
			{
				aDoc.PrintError();
				MessageBoxW(_gWindow, L"Could not save as XML", L"Error saving XML", MB_OK);
			}
		}
	}

	void GameEngine::OnEngineReset()
	{
		objects.clear();
	}

	void GameEngine::Repaint()
	{
		RedrawWindow(_gWindow, NULL, NULL, RDW_INVALIDATE);
	}

	void GameEngine::Hide()
	{
		ShowWindow(_gWindow, SW_HIDE);
	}

	void GameEngine::Show()
	{
		ShowWindow(_gWindow, SW_SHOW);
	}

	void GameEngine::Update()
	{
		auto current_time_step = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> time_step(current_time_step - last_time_step);
		float dt = time_step.count();

		for (std::vector<Renderable>::iterator object = objects.begin(); object != objects.end(); object++)
		{
			object->storeFrame();				// store the position, velocity, inertia etc
			object->updateFrame(dt);			// update the position based on the velocity etc
			if (collisionsDetected(*object))
			{
				object->previousFrame();		// if the new position is in collision with another object
												// revert to previous position and use more accurate handling
			}
		}

		last_time_step = current_time_step;

		Repaint();
	}

	void GameEngine::Close()
	{
		DestroyWindow(_gWindow);
	}

	bool GameEngine::collisionsDetected(Renderable obj)
	{
		return false;
	}

	HWND GameEngine::createSimpleToolbar(HWND hWndParent)
	{
		// Define the buttons.
		// IDM_NEW, IDM_0PEN, and IDM_SAVE are application-defined command IDs.

		const int numButtons = 3;
		TBBUTTON tbButtons3[numButtons] =
		{
			{ STD_FILENEW,  ID_FILE_NEW,  TBSTATE_ENABLED | TBSTATE_WRAP, BTNS_BUTTON,{ 0 }, 0L, 0 },
			{ STD_FILEOPEN, ID_FILE_LOAD, TBSTATE_ENABLED | TBSTATE_WRAP, BTNS_BUTTON,{ 0 }, 0L, 0 },
			{ STD_FILESAVE, ID_FILE_SAVE, TBSTATE_ENABLED | TBSTATE_WRAP, BTNS_BUTTON,{ 0 }, 0L, 0 }
		};

		// Create the toolbar window.
		HWND hWndToolbar = CreateWindowEx(0, TOOLBARCLASSNAME, NULL,
			WS_CHILD | WS_VISIBLE | CCS_VERT | WS_BORDER, 0, 0, 0, 0,
			hWndParent, NULL, hInstance, NULL);

		// Create the image list.
		hImageList = ImageList_Create(24, 24,                   // Dimensions of individual bitmaps.  
			ILC_COLOR16 | ILC_MASK,   // Ensures transparent background.
			numButtons, 0);

		// Set the image list.
		SendMessage(hWndToolbar, TB_SETIMAGELIST, 0, (LPARAM)hImageList);

		// Load the button images.
		SendMessage(hWndToolbar, TB_LOADIMAGES, (WPARAM)IDB_STD_LARGE_COLOR, (LPARAM)HINST_COMMCTRL);

		// Add them to the toolbar.
		SendMessage(hWndToolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
		SendMessage(hWndToolbar, TB_ADDBUTTONS, numButtons, (LPARAM)&tbButtons3);

		return hWndToolbar;
	}

	LRESULT GameEngine::handleWindowsMessage(cwc::glWindow* window, UINT message, WPARAM wParam, LPARAM lParam)
	{
		HWND hWnd = window->getWindowHandle();
		switch (message)
		{
		case WM_COMMAND:
		{
			switch (LOWORD(wParam))
			{
			case ID_VIEWMODE_ROTATE:
			{
				window->OnRotateModeSelected();
			}
			break;
			case ID_VIEWMODE_PAN:
			{
				window->OnPanModeSelected();
			}
			break;
			case ID_VIEWMODE_ZOOM:
			{
				window->OnZoomModeSelected();
			}
			break;
			case ID_FILE_NEW:
				window->OnEngineReset();
				break;
			case ID_FILE_LOAD:
				window->OnXMLLoad();
				break;
			case ID_FILE_SAVE:
				window->OnXMLSave();
				break;
			case IDM_ABOUT:
			{
				DialogBox(hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, GameEngine::About);
			}
			break;
			case IDM_EXIT:
				window->OnClose();
				break;
			default:
				return DefWindowProcW(hWnd, message, wParam, lParam);
			}
		}
		break;
		case WM_TIMER:
		{
			switch (wParam)
			{
			case IDT_TIMER1:
				window->Update();
				break;
			default:
				return DefWindowProcW(hWnd, message, wParam, lParam);
			}
		}
		break;
		case WM_MOUSEWHEEL:
		{
			int fwKeys = GET_KEYSTATE_WPARAM(wParam);
			int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
			window->OnMouseWheel(fwKeys, zDelta);
			window->Repaint();
		}
		break;
		case WM_MOUSEMOVE:
		{
			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam);

			if (GetKeyState(VK_LBUTTON) & 0x100)
			{
				window->OnLeftMouseDrag(xPos, yPos, (DWORD)wParam);
			}

			window->OnMouseMove(xPos, yPos);
			window->Repaint();
		}
		break;
		case WM_LBUTTONDOWN:
		{
			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam);
			HWND hwnd = window->getWindowHandle();
			window->OnLeftMouseDown(xPos, yPos);
			window->OnRender();
		}
		break;
		case WM_RBUTTONDOWN:
		{
			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam);
			HWND hwnd = window->getWindowHandle();
			window->OnRightMouseDown(xPos, yPos);
			window->OnRender();
		}
		break;
		case WM_LBUTTONUP:
		{
			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam);
			window->OnLeftMouseUp(xPos, yPos);
			window->Repaint();
		}
		break;
		case WM_RBUTTONUP:
		{
			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam);
			window->OnRightMouseUp(xPos, yPos);
			window->Repaint();
		}
		break;
		case WM_KEYDOWN:
		{
			window->OnKeyDown(wParam, lParam);
			window->Repaint();
		}
		break;
		case WM_PAINT:
		{
			window->OnRender();
		}
		break;
		case WM_CLOSE:
			window->OnClose();
			break;
		default:
			return DefWindowProcW(hWnd, message, wParam, lParam);
		}

		return DefWindowProcW(hWnd, message, wParam, lParam);
	}

	LRESULT CALLBACK GameEngine::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (_gWinInstances.empty())
		{
			return DefWindowProcW(hWnd, message, wParam, lParam);
		}
		else
		{
			HWND CurrentWindow = GetActiveWindow();
			if (!CurrentWindow)
			{
				return DefWindowProcW(hWnd, message, wParam, lParam);
			}

			std::list<glWindow*>::iterator i = _gWinInstances.begin();

			while (i != _gWinInstances.end())
			{
				if ((*i)->getWindowHandle() == CurrentWindow)
				{
					return handleWindowsMessage(*i,message, wParam, lParam);
				}
				i++;
			}
		}
		return 0;
	}

	// Message handler for about box.
	INT_PTR CALLBACK GameEngine::About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
	{
		UNREFERENCED_PARAMETER(lParam);
		switch (message)
		{
		case WM_INITDIALOG:
			return (INT_PTR)TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			break;
		}
		return (INT_PTR)FALSE;
	}