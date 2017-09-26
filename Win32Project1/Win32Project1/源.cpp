#include <cstdlib>
#include "windows.h"
using namespace std;
class Point
{
public:
	Point(double x1 = 0.0, double y1 = 0.0)
	{
		x = x1; y = y1;
	}
	double get_x() const { return x; }
	double get_y() const { return y; }
private:
	double x, y;
};
void DrawTriangle(HWND hwnd, HDC hdc)
{
	// ��ÿͻ�����
	RECT r;
	GetClientRect(hwnd, &r);

	// ����ӳ��ģʽ
	SetMapMode(hdc, MM_ISOTROPIC);
	// ���ô������귶Χ
	SetWindowExtEx(hdc, 100, 100, NULL);
	// �����ӿ����귶Χ
	SetViewportExtEx(hdc, r.right, r.bottom, NULL);
	// ����������
	SelectObject(hdc, CreatePen(PS_SOLID, 3, RGB(255, 0, 0)));
	Point p[] = { Point(30,40),Point(42,55),Point(30,70),Point(50,70),Point(60,80),Point(70,70),
		Point(90,70),Point(75,55),Point(90,40),Point(70,40),Point(60,30),Point(50,40) };
	MoveToEx(hdc, p[0].get_x(), p[0].get_y(), NULL);
	for (int i = 0; i<12; i++)
	{
		if (i == 11)
		{
			LineTo(hdc, p[0].get_x(), p[0].get_y());
			continue;
		}
		LineTo(hdc, p[i + 1].get_x(), p[i + 1].get_y());
	}
	DeleteObject(SelectObject(hdc, CreatePen(PS_SOLID, 3, RGB(255, 0, 0))));
}

LRESULT CALLBACK ccc_win_proc(HWND hwnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam);
int APIENTRY WinMain(HINSTANCE hInstance,   // ��ǰʵ�����
	HINSTANCE hPrevInstance,  // ǰʵ�����
	LPSTR     lpCmdLine,     // �����в���
	int       nShowCmd)      // ָ�����������ʾ
{
	MSG msg;	// ����һ��������Ϣ�ı���
	WNDCLASS wndclass;
	if (!hPrevInstance)
	{
		wndclass.style = CS_HREDRAW | CS_VREDRAW;
		wndclass.lpfnWndProc = ccc_win_proc;  // ָ�����ں�������Ϣ������ڣ�
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;
		wndclass.hInstance = hInstance;
		wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);  	// ָ���������ͼ��
		wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);	// ָ��������Ĺ��
		wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		// ָ����䴰�ڱ����Ļ�ˢ
		wndclass.lpszMenuName = NULL;
		wndclass.lpszClassName = "CCC_WIN";  // ����������

		RegisterClass(&wndclass);
	}
	// ��ʼ�����ڣ����ɴ��ڲ���ʾ���´���
	char title[80];
	GetModuleFileName(hInstance, title, sizeof(title));  // �õ���ǰ���г����ȫ·��
	HWND hwnd = CreateWindow("CCC_WIN",
		title,
		WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		GetSystemMetrics(SM_CYFULLSCREEN) * 3 / 4,
		GetSystemMetrics(SM_CYFULLSCREEN) * 3 / 4,
		NULL,
		NULL,
		hInstance,
		0);  // ��ע��Ĵ��������ɴ���ʵ��
			 // ��ʾ����
	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);   // ��Update Region���գ�����WM_PAINT��Ϣ

	while (GetMessage(&msg, NULL, 0, 0)) 	// ��Ϣѭ�������û�����������Ӧ
	{
		TranslateMessage(&msg); 	// ���������Ϣת�����ַ���Ϣ����������Ϣ����
		DispatchMessage(&msg);		// �ַ���Ϣ������Ϣ��������Ϣ���͵����ڴ�����
	}
	return msg.wParam;
}
LRESULT CALLBACK ccc_win_proc(HWND hwnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam)
{
	PAINTSTRUCT ps; 		// the display's paint struct
	HDC mainwin_hdc;
	switch (message)
	{
	case WM_PAINT:
		mainwin_hdc = BeginPaint(hwnd, &ps);
		DrawTriangle(hwnd, mainwin_hdc);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		// ����Ĭ�ϵ���Ϣ������, ����������Ϣ���д���
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}
