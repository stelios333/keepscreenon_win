// trayapp.cpp
#include <windows.h>
#include <shellapi.h>
#include <tchar.h>

#define ID_TRAY_APP_ICON    1
#define WM_TRAYNOTIFY       WM_USER + 1
#define IDM_EXIT            1001
#define IDM_TOGGLE_KEEP_ON  1002

NOTIFYICONDATA nid = {0};
HINSTANCE hInst;
BOOL keepScreenOn = false;

void UpdateScreenState()
{
    if (keepScreenOn)
    {
        // Prevent screen from turning off
        SetThreadExecutionState(ES_CONTINUOUS | ES_DISPLAY_REQUIRED);
    }
    else
    {
        // Restore normal power management
        SetThreadExecutionState(ES_CONTINUOUS);
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_TRAYNOTIFY:
            if (lParam == WM_RBUTTONDOWN)
            {
                POINT pt;
                GetCursorPos(&pt);
                
                HMENU hMenu = CreatePopupMenu();
                if (hMenu)
                {
                    InsertMenu(hMenu, -1, MF_BYPOSITION | (keepScreenOn ? MF_CHECKED : MF_UNCHECKED), 
                              IDM_TOGGLE_KEEP_ON, _T("Keep Screen On"));
                    InsertMenu(hMenu, -1, MF_BYPOSITION, IDM_EXIT, _T("Exit"));
                    
                    SetForegroundWindow(hwnd);
                    TrackPopupMenu(hMenu, TPM_BOTTOMALIGN | TPM_LEFTALIGN | TPM_RIGHTBUTTON,
                                 pt.x, pt.y, 0, hwnd, NULL);
                    DestroyMenu(hMenu);
                }
            }
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case IDM_TOGGLE_KEEP_ON:
                    keepScreenOn = !keepScreenOn;
                    UpdateScreenState();
                    break;
                    
                case IDM_EXIT:
                    Shell_NotifyIcon(NIM_DELETE, &nid);
                    DestroyWindow(hwnd);
                    break;
            }
            break;

        case WM_DESTROY:
            // Reset screen state before exiting
            SetThreadExecutionState(ES_CONTINUOUS);
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    hInst = hInstance;

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = _T("TrayAppClass");
    RegisterClass(&wc);

    HWND hwnd = CreateWindow(
        _T("TrayAppClass"),
        _T("Screen Keeper"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        CW_USEDEFAULT, CW_USEDEFAULT,
        NULL, NULL, hInstance, NULL
    );

    if (!hwnd)
        return 1;

    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = hwnd;
    nid.uID = ID_TRAY_APP_ICON;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid.uCallbackMessage = WM_TRAYNOTIFY;
    nid.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    _tcscpy_s(nid.szTip, _T("Screen Keeper"));
    Shell_NotifyIcon(NIM_ADD, &nid);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}