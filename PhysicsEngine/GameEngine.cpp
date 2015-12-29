#include "GameEngine.h"
#include "SceneManager.h"
#include "tiny_obj_loader.h"
#include "resource.h"

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

		ShowWindow(_gWindow, SW_SHOW);
		UpdateWindow(_gWindow);
		initializeMenus();
		sceneRenderer.onInit();
	}

	void GameEngine::OnRender(void)
{
	std::vector<GeoModel3D*> object_models;
	std::vector<Renderable> objects = sceneManager.getObjects();
	Camera camera = sceneManager.getCamera();
	sceneManager.update();
	sceneRenderer.renderScene(camera,objects);
}

	void GameEngine::OnIdle() { }

	void GameEngine::OnResize(int w, int h) {}
	void GameEngine::OnClose(void)
	{
		DestroyWindow(_gWindow);
		PostQuitMessage(0);
	}
	void GameEngine::OnMouseDown(int button, int x, int y) 
	{
		sceneManager.onMouseDown(button, x, y);
		glutPostRedisplay();
	}    
	void GameEngine::OnMouseUp(int button, int x, int y) 
	{
		sceneManager.onMouseUp(button, x, y);
		glutPostRedisplay();
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
			sceneManager.onKeyPress(nKey,cAscii);
		}

		glutPostRedisplay();
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

	void GameEngine::initializeMenus()
	{
		initializeMenuBar();
		initializeMouseMenus();
	}

	void GameEngine::initializeMenuBar()
	{
		HWND hwnd = GetActiveWindow();
		HMENU hMenu = LoadMenu(NULL, MAKEINTRESOURCE(IDC_GAMEENGINE));
		SetMenu(hwnd, hMenu);
	}

	void GameEngine::initializeMouseMenus()
	{
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

	void GameEngine::Repaint()
	{
	}

	void GameEngine::Hide()
	{

	}

	void GameEngine::Show()
	{

	}

	void GameEngine::Close()
	{

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
			case IDM_ABOUT:
			{
				DialogBox(hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, GameEngine::About);
			}
			break;
			case IDM_EXIT:
				window->OnClose();
				break;
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code that uses hdc here...
			EndPaint(hWnd, &ps);
		}
		break;
		case WM_CLOSE:
			window->OnClose();
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}

		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	LRESULT CALLBACK GameEngine::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		if (_gWinInstances.empty())
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		else
		{
			HWND CurrentWindow = GetActiveWindow();
			if (!CurrentWindow)
			{
				return DefWindowProc(hWnd, message, wParam, lParam);
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