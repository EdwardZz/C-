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
	// 获得客户区域
	RECT r;
	GetClientRect(hwnd, &r);

	// 设置映像模式
	SetMapMode(hdc, MM_ISOTROPIC);
	// 设置窗口坐标范围
	SetWindowExtEx(hdc, 100, 100, NULL);
	// 设置视口坐标范围
	SetViewportExtEx(hdc, r.right, r.bottom, NULL);
	// 绘制三角形
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
int APIENTRY WinMain(HINSTANCE hInstance,   // 当前实例句柄
	HINSTANCE hPrevInstance,  // 前实例句柄
	LPSTR     lpCmdLine,     // 命令行参数
	int       nShowCmd)      // 指明窗口如何显示
{
	MSG msg;	// 声明一个保存消息的变量
	WNDCLASS wndclass;
	if (!hPrevInstance)
	{
		wndclass.style = CS_HREDRAW | CS_VREDRAW;
		wndclass.lpfnWndProc = ccc_win_proc;  // 指定窗口函数（消息处理入口）
		wndclass.cbClsExtra = 0;
		wndclass.cbWndExtra = 0;
		wndclass.hInstance = hInstance;
		wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);  	// 指定窗口类的图标
		wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);	// 指定窗口类的光标
		wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
		// 指定填充窗口背景的画刷
		wndclass.lpszMenuName = NULL;
		wndclass.lpszClassName = "CCC_WIN";  // 窗口类名称

		RegisterClass(&wndclass);
	}
	// 初始化窗口，生成窗口并显示更新窗口
	char title[80];
	GetModuleFileName(hInstance, title, sizeof(title));  // 得到当前运行程序的全路径
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
		0);  // 用注册的窗口类生成窗口实例
			 // 显示窗口
	ShowWindow(hwnd, nShowCmd);
	UpdateWindow(hwnd);   // 若Update Region不空，则发送WM_PAINT消息

	while (GetMessage(&msg, NULL, 0, 0)) 	// 消息循环，对用户操作进行响应
	{
		TranslateMessage(&msg); 	// 将虚拟键消息转换成字符消息，再送入消息队列
		DispatchMessage(&msg);		// 分发消息，将消息队列中消息发送到窗口处理函数
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
		// 调用默认的消息处理函数, 对其他的消息进行处理
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}
