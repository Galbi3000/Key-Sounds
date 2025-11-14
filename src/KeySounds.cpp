// KeySounds.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

#define MAX_LOADSTRING 100
#define STATUS_ICON_ID		(WM_USER + 1)	// ID for notifications from status icon

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];								// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];								// The title bar text
HWND hMainWnd;
HHOOK hKeyLLHook;								// Handle to keyboard hook
NOTIFYICONDATA taskbarIconData;

// Foward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
void				Tidy(void);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	LowLevelKeyboardProc(int, WPARAM, LPARAM);

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_KEYSOUNDS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)) 
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_KEYSOUNDS);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	
	Tidy();		// Clear up any loose ends before exiting the program

	return msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_KEYSOUNDS);
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= NULL;

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	DWORD dwLastError;
	hInst = hInstance; // Store instance handle in our global variable
	HICON hIcon;

	hMainWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hMainWnd)
	{
		return FALSE;
	}

	ShowWindow(hMainWnd, SW_HIDE);
	UpdateWindow(hMainWnd);

	// Set up the keyboard hook
//	hKeyLLHook = SetWindowsHookEx(13, LowLevelKeyboardProc, hInstance, 0);
	hKeyLLHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, hInstance, 0);
	if(hKeyLLHook == 0)
	{
		dwLastError = GetLastError();
		return FALSE;
	}

	// Display the system tray icon
	memset(&taskbarIconData, 0, sizeof(NOTIFYICONDATA));	// Initialize the structure to all zero value
	taskbarIconData.cbSize = sizeof(NOTIFYICONDATA);	// Must be set to make data valid
	taskbarIconData.hWnd = hMainWnd;	// The main window will deal with messages from the icon
	taskbarIconData.uID = STATUS_ICON_ID;	// The ID number of the icon, defined as WM_USER+1. Used to identify messages from icons.
	taskbarIconData.uCallbackMessage = STATUS_ICON_ID;
	hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KEYSOUNDS));
	taskbarIconData.hIcon = hIcon;
	strcpy_s(taskbarIconData.szTip, "Key Sounds - Version 1.0 Beta - Copyright 2004 TannSoft");
	taskbarIconData.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;

	Shell_NotifyIcon(NIM_ADD, &taskbarIconData);

	return TRUE;
}

//
// FUNCTION: Tidy()
//
// PURPOSE: Cleans up loose ends before program exit.
//
// No paramiters needed. Most items to tidy up are global.
void Tidy(void)
{
	// First remove the taskbar icon
	memset(&taskbarIconData, 0, sizeof(NOTIFYICONDATA));
	taskbarIconData.cbSize = sizeof(NOTIFYICONDATA);
	taskbarIconData.hWnd = hMainWnd;
	taskbarIconData.uID = STATUS_ICON_ID;
	Shell_NotifyIcon(NIM_DELETE, &taskbarIconData);

	// Now most importantly, remove the keyboard hook!
	UnhookWindowsHookEx(hKeyLLHook);
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hInst, IDS_HELLO, szHello, MAX_LOADSTRING);

	switch (message) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				case IDM_ABOUT:
				   break;
				case IDM_EXIT:
				   DestroyWindow(hWnd);
				   break;
				default:
				   return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			// TODO: Add any drawing code here...
			RECT rt;
			GetClientRect(hWnd, &rt);
			DrawText(hdc, szHello, strlen(szHello), &rt, DT_CENTER);
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_USER:					// Keyboard hook sent a message!
			// Make a sound!
			switch (wParam)
			{
				case 1:
					PlaySound("IDR_TYPEWAVE", hInst, SND_RESOURCE | SND_ASYNC);
					break;
				case 2:
					break;
			}
			wParam = 0;
			break;
		case STATUS_ICON_ID:			// Defined as WM_USER+1... Process messages from the taskbar icon here
			if(lParam == WM_RBUTTONDOWN)
			{
				if(MessageBox(hWnd, "Are you sure you want to close Key Sounds?", "Close Key Sounds Request", MB_ICONQUESTION|MB_YESNO)==IDYES)
					DestroyWindow(hWnd);
			}
			else if(lParam == WM_LBUTTONDBLCLK)
			{
			   DialogBox(hInst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
			}
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Mesage handler for about box.
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if(nCode <0)
		return CallNextHookEx(hKeyLLHook, nCode, wParam, lParam);
	else
	{
		switch (wParam)
		{
			case WM_KEYDOWN:
				// Send message to WndProc to tell it to make a sound
				SendMessage(hMainWnd, WM_USER, 1, lParam);
				break;
			case WM_SYSKEYDOWN:
				// Send message to WndProc to tell it to make a sound
				SendMessage(hMainWnd, WM_USER, 2, lParam);
				break;
		}
		return CallNextHookEx(hKeyLLHook, nCode, wParam, lParam);
	}
}
