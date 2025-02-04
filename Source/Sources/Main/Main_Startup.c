
//<<>-<>>---------------------------------------------------------------------()
/*
	Routines de d幦arrage.
									      */
//()-------------------------------------------------------------------<<>-<>>//

// 中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中 //
// 中�									  中� //
// 中� Donn嶪s								  中� //
// 中�									  中� //
// 中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中 //

#include "..\Includes\Editor.h"
#include "..\Includes\Prototypes.h"
#include "..\Includes\Structures.h"
#include "..\Includes\Texts.h"

extern HINSTANCE	hInstance;
extern HINSTANCE	hDirectSound;
extern HMENU		hMenu;
extern HWND		hWnd;
extern HANDLE		AppMutex;
extern ULONG		InfoMemoryUsedByUndo;


// 中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中 //
// 中�									  中� //
// 中� Fonctions							  中� //
// 中�									  中� //
// 中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中 //

#pragma argsused
int APIENTRY WinMain(HINSTANCE hWinCInstance, HINSTANCE hWinPInstance, LPSTR CmdLine, int CmdShow)
{
	MSG	msg;

	hInstance = hWinCInstance;

	if (!Initialise_GetVersion())
		goto Init_Failure0;
	if (!Initialise_GetDeviceCaps())
		goto Init_Failure0;
	if (!Initialise_LockInstance())
		goto Init_Failure0;
	if (!Initialise_WindowsClasses())
		goto Init_Failure1;
	if (!Keyboard_InitialiseHook())
		goto Init_Failure1;
	if (!Initialise_Window())
		goto Init_Failure2;

	while (GetMessage(&msg,NULL,0,0))
		{
		Minimap_Messages(&msg);
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		}

	if (InfoMemoryUsedByUndo != 0)
		Misc_MessageBoxExt(NULL,szGlobalAllocErr,szInternalError,szMessageBoxExtOk,MB_ICONHAND);

	Keyboard_ResetHook();
	#if (LOCK_MULTIPLERUNS)
	CloseHandle(AppMutex);
	#endif
	if (hDirectSound) FreeLibrary(hDirectSound);
	return(msg.wParam);

//--- Erreurs d'initialisation ---

Init_Failure2:
	Keyboard_ResetHook();
Init_Failure1:
	#if (LOCK_MULTIPLERUNS)
	CloseHandle(AppMutex);
	#endif
Init_Failure0:
	return(0);
}


// 姣遙 Test les caract廨istiques du syst鋗e 垂垂垂垂垂垂垂垂垂垂垂垂垂垂�

//--- Test la version du syst鋗e d'exploitation ---

int Initialise_GetVersion()
{
	OSVERSIONINFO osVer;

	osVer.dwOSVersionInfoSize = sizeof(osVer);
	if (GetVersionEx(&osVer) == 0)
		{
		MessageBox(NULL,szVersionErr,szInitErr,MB_OK|MB_ICONHAND);
		return(0);
		}
	if (osVer.dwPlatformId == VER_PLATFORM_WIN32s)
		{
		MessageBox(NULL,szWinVersionErr,szInitErr,MB_OK|MB_ICONHAND);
		return(0);
		}

	return(1);
}

//--- Test les caract廨istiques de la carte graphique ---

int Initialise_GetDeviceCaps()
{
	HWND	hWnd;
	HDC	hDC;
	int	DeviceCaps;

	hWnd = GetDesktopWindow();
	hDC = GetWindowDC(hWnd);
	DeviceCaps = GetDeviceCaps(hDC,RASTERCAPS);
	ReleaseDC(hWnd,hDC);

	if ( !(DeviceCaps&(RC_BITBLT|RC_DI_BITMAP|RC_STRETCHBLT|RC_PALETTE)) )
		{
		MessageBox(NULL,szMissingCapsErr,szInitErr,MB_OK|MB_ICONHAND);
		return(0);
		}

	return(1);
}


// 姣遙 Emp鋃he le lancement de plusieurs instances 垂垂垂垂垂垂垂垂垂垂姣

int Initialise_LockInstance()
{
	#if (LOCK_MULTIPLERUNS)
	AppMutex = CreateMutex(NULL,FALSE,szAppName);
	if (!AppMutex)
		{
		MessageBox(NULL,szMutexErr,szInitErr,MB_OK|MB_ICONHAND);
		return(0);
		}
	if (GetLastError() == ERROR_ALREADY_EXISTS)
		{
		CloseHandle(AppMutex);
		MessageBox(NULL,szAlreadyExistsErr,szInitErr,MB_OK|MB_ICONINFORMATION);
		return(0);
		}
	#endif
	return(1);
}


// 姣遙 Initialisation des classes de fen皻res 垂垂垂垂垂垂垂垂垂垂垂垂垂�

int Initialise_WindowsClasses()
{
	WNDCLASSEXA wndClass;

	wndClass.cbSize = sizeof(wndClass);
	wndClass.style = CS_OWNDC;
	wndClass.lpfnWndProc = Window_Proc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadImage(hInstance,MAKEINTRESOURCE(1),IMAGE_ICON,16,16,0);
	wndClass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndClass.hbrBackground = NULL;
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = szAppName;
	wndClass.hIconSm = wndClass.hIcon;
	if (RegisterClassEx(&wndClass) == 0)
		{
		MessageBox(NULL,szWindowErr,szInitErr,MB_OK|MB_ICONHAND);
		return(0);
		}

	wndClass.cbSize = sizeof(wndClass);
	wndClass.style = CS_OWNDC|CS_NOCLOSE;
	wndClass.lpfnWndProc = Disk_ProcessMessages;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadImage(hInstance,MAKEINTRESOURCE(1),IMAGE_ICON,16,16,0);
	wndClass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndClass.hbrBackground = NULL;
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = szDiskClass;
	wndClass.hIconSm = wndClass.hIcon;
	if (RegisterClassEx(&wndClass) == 0)
		{
		MessageBox(NULL,szWindowErr,szInitErr,MB_OK|MB_ICONHAND);
		return(0);
		}

	wndClass.cbSize = sizeof(wndClass);
	wndClass.style = CS_DBLCLKS|CS_SAVEBITS|CS_BYTEALIGNWINDOW;
	wndClass.lpfnWndProc = DefDlgProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = DLGWINDOWEXTRA;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadImage(hInstance,MAKEINTRESOURCE(1),IMAGE_ICON,16,16,0);
	wndClass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = szDialogClass;
	wndClass.hIconSm = wndClass.hIcon;
	if (RegisterClassEx(&wndClass) == 0)
		{
		MessageBox(NULL,szWindowErr,szInitErr,MB_OK|MB_ICONHAND);
		return(0);
		}

	wndClass.cbSize = sizeof(wndClass);
	wndClass.style = CS_DBLCLKS|CS_SAVEBITS|CS_BYTEALIGNWINDOW|CS_NOCLOSE;
	wndClass.lpfnWndProc = DefDlgProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = DLGWINDOWEXTRA;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadImage(hInstance,MAKEINTRESOURCE(1),IMAGE_ICON,16,16,0);
	wndClass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = szMessageClass;
	wndClass.hIconSm = wndClass.hIcon;
	if (RegisterClassEx(&wndClass) == 0)
		{
		MessageBox(NULL,szWindowErr,szInitErr,MB_OK|MB_ICONHAND);
		return(0);
		}

	InitCommonControls();
	return(1);
}


// 姣遙 Initialisation de la fen皻re principale 垂垂垂垂垂垂垂垂垂垂垂垂姣

int Initialise_Window(void)
{
	hMenu = CreateMenu_MAINMENU();
	if (!hMenu)
		{
		Misc_PrintError(NULL,szWindowMenuErr,szInitErr,MB_ICONHAND);
		return(0);
		}
	Misc_InitialiseMenus(hMenu,MainMenu);

	hWnd = CreateWindowEx(0,szAppName,szWindowTitle,WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN,0,0,640,480,NULL,hMenu,hInstance,(void *)WINDOW_MAIN);
	if (!hWnd)
		{
		if (hMenu)
			{
			DestroyMenu(hMenu);
			Misc_ResetMenus(MainMenu);
			}
		if (GetLastError())
			Misc_PrintError(NULL,szWindowErr,szInitErr,MB_ICONHAND);
		return(0);
		}
	else
		{
		#if (START_MAXIMIZED)
		ShowWindow(hWnd,SW_MAXIMIZE);
		#else
		ShowWindow(hWnd,SW_SHOWNORMAL);
		#endif
		UpdateWindow(hWnd);
		}

	return(1);
}

// 中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中 //
// 中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中中 //
// END
