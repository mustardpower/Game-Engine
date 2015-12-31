#include "GameEngine.h"
#include "SceneManager.h"
#include "tiny_obj_loader.h"
#include "resource.h"

#include <string>

	// When OnInit is called, a render context (in this case GLUT-GameEngine) 
	// is already available!

	#define MAX_LOADSTRING 100
	WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
	WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

	HINSTANCE GameEngine::hInstance;

	GameEngine::GameEngine(char* GameEngineTitle) : cwc::glWindow()
	{
		OnInit();
	}

	//
	//  FUNCTION: MyRegisterClass()
	//
	//  PURPOSE: Registers the window class.
	//
	ATOM GameEngine::RegisterClass(HINSTANCE hInstance)
	{
		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = GameEngine::WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAMEENGINE));
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = szWindowClass;
		wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

		return RegisterClassExW(&wcex);
	}

	void GameEngine::OnInit()
	{
		_gWinInstances.push_back(this);

		// Initialize global strings
		LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
		LoadStringW(hInstance, IDC_GAMEENGINE, szWindowClass, MAX_LOADSTRING);

		hInstance = GetModuleHandle(NULL); // Store instance handle in our global variable
		RegisterClass(hInstance);
		_gWindow = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
		Show();
		UpdateWindow(_gWindow);
		initializeMenuBar();
		sceneRenderer.onInit(_gWindow);

		GeoModel3D* model = new GeoModel3D("cube");
		sceneRenderer.createVAO(model);
		Renderable* cube1 = new Renderable(model, glm::vec3(0.0, 0.0, 0.0));
		Renderable* cube2 = new Renderable(model, glm::vec3(10.0, 0.0, 0.0));
		sceneManager.addObject(*cube1);
		sceneManager.addObject(*cube2);
	}

	void GameEngine::OnRender()
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(_gWindow, &ps);
		std::vector<GeoModel3D*> object_models;
		std::vector<Renderable> objects = sceneManager.getObjects();
		Camera camera = sceneManager.getCamera();
		sceneManager.update();
		sceneRenderer.renderScene(hdc,camera,objects);
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
		sceneManager.onLeftMouseDown(x, y);
	}  
	void GameEngine::OnRightMouseDown(int x, int y)
	{
		sceneManager.onRightMouseDown(x, y);
	}
	void GameEngine::OnLeftMouseUp(int x, int y) 
	{
		sceneManager.onLeftMouseUp(x, y);
	}
	void GameEngine::OnRightMouseUp(int x, int y)
	{
		sceneManager.onRightMouseUp(x, y);
	}
	void GameEngine::OnMouseWheel(int nWheelNumber, int nDirection, int x, int y){}
	void GameEngine::OnKeyDown(int nKey, char cAscii)
	{       
		if (cAscii == 27) // 0x1b = ESC
		{
			this->Close(); // Close GameEngine!
		}
		else
		{
			sceneManager.onKeyPress(nKey);
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
		switch (menuOption)
		{
		case 1:
			glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
			break;
		case 2:
			glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
			break;
		case 3:
			glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
			break;
		case 4:
			glClearColor(1.0f, 0.5f, 0.0f, 0.0f);
			break;
		default:
			glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
			break;
		}

		glutPostRedisplay();
	}

	void GameEngine::OnMenuBarSelection(int menuOption)
	{
		switch (menuOption)
		{
		case 1:
			glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
			break;
		case 2:
			glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
			break;
		case 3:
			glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
			break;
		case 4:
			glClearColor(1.0f, 0.5f, 0.0f, 0.0f);
			break;
		default:
			glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
			break;
		}

		glutPostRedisplay();
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

	//! Called when Mouse is moved (without pressing any button)
	void GameEngine::OnMouseMove(int x, int y)
	{
	}

	void  GameEngine::SetFullscreen(bool bFullscreen)
	{
	}

	void GameEngine::OnLeftMouseDrag(int x, int y)
	{
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
			bool success = sceneManager.fromXML(file_name);
			if (!success)
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
			bool success = sceneManager.toXML(file_name);
			if (!success)
			{
				MessageBoxW(_gWindow, L"Could not save as XML", L"Error saving XML", MB_OK);
			}
		}
	}

	void GameEngine::OnEngineReset()
	{
		sceneManager.reset();
	}

	void GameEngine::Repaint()
	{
		printf("Update window\n");
		InvalidateRect(_gWindow,NULL, TRUE);
		UpdateWindow(_gWindow);
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
		printf("Update window\n");
		UpdateWindow(_gWindow);
	}

	void GameEngine::Close()
	{
		DestroyWindow(_gWindow);
	}

	LRESULT GameEngine::handleWindowsMessage(cwc::glWindow* window, UINT message, WPARAM wParam, LPARAM lParam)
	{
		HWND hWnd = window->getWindowHandle();
		switch (message)
		{
		case WM_COMMAND:
		{
			switch (wParam)
			{
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
		case WM_LBUTTONDOWN:
		{
			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam);
			window->OnLeftMouseDown(xPos, yPos);
			window->Repaint();
		}
		break;
		case WM_RBUTTONDOWN:
		{
			int xPos = GET_X_LPARAM(lParam);
			int yPos = GET_Y_LPARAM(lParam);
			window->OnRightMouseDown(xPos, yPos);
			window->Repaint();
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
			printf("WM_PAINT sent\n");
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