/* -------------------------------------------------------------------
MyWindows.c -- ��������ģ��
��Windows ������ƣ�SDK������Ƶ�̳�
--------------------------------------------------------------------*/

#include <windows.h>

#define ID_EDIT  1
#define ID_EDIT2   2
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR szAppName[] = TEXT("PopPad1");
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("���������Ҫ�� Windows NT ����ִ�У�"), szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName,
		TEXT("ʵ��"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HWND hwndEdit;
	static HWND hwndEdit2;
	TCHAR szEdit[800] = { 0 };
	RECT rect;
	static int cxChar, cyChar;
	switch (message)
	{
	case WM_CREATE:
		cxChar = LOWORD(GetDialogBaseUnits());
		cyChar = HIWORD(GetDialogBaseUnits());
		hwndEdit = CreateWindow(TEXT("edit"),
			NULL, WS_CHILD | WS_VISIBLE, 29, cyChar, 20*cxChar,cyChar/4, hwnd, (HMENU)ID_EDIT,
			((LPCREATESTRUCT)lParam)->hInstance, NULL);
		hwndEdit2 = CreateWindow(TEXT("edit"),
			NULL, WS_CHILD | WS_VISIBLE, 10, cyChar * 2, 20 * cxChar, 7 * cyChar / 4, hwnd, (HMENU)ID_EDIT2,
			((LPCREATESTRUCT)lParam)->hInstance, NULL); \
			PlaySound("res/younv.wav", FALSE, SND_ASYNC);
		return 0;
	case WM_PAINT:
		InvalidateRect(hwnd, &rect, TRUE);
		return 0;
	case WM_SETFOCUS:
		SetFocus(hwndEdit);
		return 0;
	case WM_SIZE:
		MoveWindow(hwndEdit, 0, 0, LOWORD(lParam) / 4, HIWORD(lParam) / 4, TRUE);
		MoveWindow(hwndEdit2, 0, HIWORD(lParam) / 4 +10, LOWORD(lParam) / 4, HIWORD(lParam) / 4, TRUE);
		return 0;
	case WM_COMMAND:
		if (LOWORD(wParam) == ID_EDIT)
		{
			if ((HIWORD(wParam) == EN_ERRSPACE) || (HIWORD(wParam) == EN_MAXTEXT))
			{
				MessageBox(hwnd, TEXT("EDit control out of space"),
					szAppName, MB_OK | MB_ICONSTOP);
			}
			else if (HIWORD(wParam) == EN_CHANGE)
			{
				GetWindowText(hwndEdit, szEdit, 800);
				SetWindowText(hwndEdit2, szEdit);
			}
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
