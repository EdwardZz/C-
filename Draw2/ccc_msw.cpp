#include <cmath>
#include <cstring>
#include <cstdio>

#include "ccc_msw.h"
#include "fig.h"
#include "Resource.h"
#include <Windowsx.h>
#include"windows.h"
#define ID_TIMER  2
using namespace std;

const double DEFAULT_XMIN = -10;
const double DEFAULT_YMIN = 10;
const double DEFAULT_XMAX = 10;
const double DEFAULT_YMAX = -10;

GraphicWindow cwin;
extern int ccc_win_main(int); 

long FAR PASCAL ccc_win_proc(HWND hwnd, UINT message, UINT wParam, LONG lParam) // 循环部分
{
	static BOOL fFlipFlop = FALSE;
   static int menuId = 0;
   static int xPos = 0;
   static int yPos = 0;
   PAINTSTRUCT ps; // the display's paint struct
   HDC mainwin_hdc;
 
   HDC hdc;

   int wmId, wmEvent;
   switch (message)
   {  
      case WM_CREATE:
		  SetTimer(hwnd, ID_TIMER, 1000, NULL);
		SetTimer(hwnd, 1, 1000, NULL);
		break;
	  
	case WM_TIMER:
		MessageBeep(-1);
		fFlipFlop = !fFlipFlop;
	      InvalidateRect(hwnd, NULL, TRUE);
		break;

	case WM_KEYDOWN:   //https://msdn.microsoft.com/en-us/library/windows/desktop/ms646281(v=vs.85).aspx
		wmId = LOWORD(wParam);
		if (wmId >= 0x30 && wmId <= 0x39) //https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731(v=vs.85).aspx
		{
			menuId = wmId;

		}
		break;

	case WM_LBUTTONDOWN:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		xPos = GET_X_LPARAM(lParam); //给出点击的位置x[0,740] y[0,700]
		yPos = GET_Y_LPARAM(lParam);			
		break;


	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		
		switch (wmId)
		{
		case IDM_FIG1:
			menuId=IDM_FIG1;
			InvalidateRect(hwnd, NULL, TRUE); //clear rect
			break;

		case IDM_FIG2:
			menuId=IDM_FIG2;
			InvalidateRect(hwnd, NULL, TRUE);
			break;

		case IDM_EXIT:
			DestroyWindow(hwnd);
			break;		
		}
		break;

	case WM_PAINT:                          // 窗口刷新消息
        mainwin_hdc = BeginPaint(hwnd, &ps);  // 置Update Region为空
		/*hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rc);
		hBrush = CreateSolidBrush(fFlipFlop ? RGB(255, 0, 0) : RGB(0, 0, 255));
		FillRect(hdc, &rc, hBrush);
		EndPaint(hwnd, &ps);
	*/

        if (menuId)
        {             
            cwin.open(hwnd, mainwin_hdc);		   
            ccc_win_main(menuId);       
        }
            else if(xPos)
            {
                  cwin.open(hwnd, mainwin_hdc);
                  cwin << Message(Point(xPos, yPos), "mouse clicked");
                  cwin << Message(Point(-1, 7), "mouse clicked");
            }

        EndPaint(hwnd, &ps);
        break;

	case WM_DESTROY:
       	KillTimer(hwnd,1); 
		KillTimer(hwnd, ID_TIMER);
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
   }
   return 0;
}

/*-------------------------------------------------------------------------*/

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
   LPSTR, int nShowCmd)
{  
   MSG msg; // 声明一个保存消息的变量
   WNDCLASS wndclass;
   // 初始化窗口类，并向操作系统注册该窗口类
   if (!hPrevInstance)
   {  
      wndclass.style = CS_HREDRAW | CS_VREDRAW;
      wndclass.lpfnWndProc = ccc_win_proc; // 指定窗口函数（消息处理入口）
      wndclass.cbClsExtra = 0;
      wndclass.cbWndExtra = 0;
      wndclass.hInstance = hInstance;
      wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // 指定窗口类的图标
      wndclass.hCursor = LoadCursor (NULL, IDC_ARROW); // 指定窗口类的光标
      wndclass.hbrBackground = (HBRUSH)GetStockObject (WHITE_BRUSH); // 指定填充窗口背景的画刷
      wndclass.lpszMenuName = MAKEINTRESOURCE(IDC_TEST2);
      wndclass.lpszClassName = "CCC_WIN"; // 窗口类名称

      RegisterClass (&wndclass);
   }
   // 初始化窗口，生成窗口并显示更新窗口
   char title[80]="绘图程序-Draw";
   
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
      0); // 用注册的窗口类生成窗口实例
   // 显示窗口
   ShowWindow(hwnd, nShowCmd);
   UpdateWindow(hwnd); // 若Update Region不空，则发送WM_PAINT消息

   while (GetMessage(&msg, NULL, 0, 0)) // 消息循环，对用户操作进行响应
   {  
      TranslateMessage(&msg); // 将虚拟键消息转换成字符消息，再送入消息队列
      DispatchMessage(&msg); // 分发消息，将消息队列中消息发送到窗口处理函数
   }
   return msg.wParam;
}

/*-------------------------------------------------------------------------*/

GraphicWindow::GraphicWindow() //cwin 就是这个类
:  _user_xmin(DEFAULT_XMIN),
   _user_ymin(DEFAULT_YMIN),
   _user_xmax(DEFAULT_XMAX),
   _user_ymax(DEFAULT_YMAX)
//: _user_xmin(0),
//_user_ymin(0),
//_user_xmax(740),
//_user_ymax(700)
{    
}

void GraphicWindow::open(HWND hwnd, HDC mainwin_hdc)
{ 
   RECT rect;   
   RECT rc;
   HBRUSH hBrush;
   //获取窗口客户区的坐标
   GetClientRect(hwnd, &rect);
   GetClientRect(hwnd, &rc);
   _disp_xmax = rect.right - 1;
   _disp_ymax = rect.bottom - 1;

   _hdc = mainwin_hdc; 

   LOGBRUSH logBrush;  
   logBrush.lbStyle = BS_HATCHED;
   logBrush.lbColor = RGB(0, 192, 192);
   logBrush.lbHatch = HS_CROSS;

   // 获得预定义的笔、画刷或字体
   SelectObject(_hdc, GetStockObject(BLACK_BRUSH));
   //SelectObject(_hdc, CreateBrushIndirect(&logBrush));
   SelectObject(_hdc, GetStockObject(BLACK_PEN));  
   SelectObject(_hdc, GetStockObject(SYSTEM_FONT));
 
   // 获取hwnd设备环境
   HDC hdc = GetDC(hwnd);      
   GetClientRect(hwnd, &rc);
   hBrush = CreateSolidBrush(RGB(0, 0, 255));
   FillRect(hdc, &rc, hBrush);
   // 释放设备上下文环境（DC）
   ReleaseDC(hwnd, hdc);
   DeleteObject(hBrush);
  /* clear();*/
}

void GraphicWindow::clear()
{  
   // 用背景色（白色）将位图清除干净
   COLORREF color = RGB(255, 255, 255);
   
   //实心刷子：系统用来绘制要填充图形的内部区域的位图
   HBRUSH brush = CreateSolidBrush(color); 
   
   // 选择对象到设备环境
   HBRUSH saved_brush = (HBRUSH)SelectObject(_hdc, brush);

   //用选入设备环境中的刷子绘制给定的矩形区域
   PatBlt(_hdc, 0, 0, _disp_xmax, _disp_ymax, PATCOPY);

   // 恢复原来画刷
   SelectObject(_hdc, saved_brush);
 
   DeleteObject(brush);
}

void GraphicWindow::coord(double xmin, double ymin,
   double xmax, double ymax)
{  
   _user_xmin = xmin;
   _user_xmax = xmax;
   _user_ymin = ymin;
   _user_ymax = ymax;
}

int GraphicWindow::user_to_disp_x(double x) const
{  
   return (int) ((x - _user_xmin) * _disp_xmax / (_user_xmax - _user_xmin));
}

int GraphicWindow::user_to_disp_y(double y) const
{  
   return (int) ((y - _user_ymin) * _disp_ymax / (_user_ymax - _user_ymin));
}

double GraphicWindow::disp_to_user_x(int x) const
{  
   return (double)x * (_user_xmax - _user_xmin) / _disp_xmax + _user_xmin;
}

double GraphicWindow::disp_to_user_y(int y) const
{  
   return (double)y * (_user_ymax - _user_ymin) / _disp_ymax + _user_ymin;
}

void GraphicWindow::point(double x, double y,COLORREF mColor)
{  
   const int POINT_RADIUS = 3;
   int disp_x = user_to_disp_x(x);
   int disp_y = user_to_disp_y(y);
   SelectObject(_hdc, CreatePen(PS_SOLID,1,mColor));
   Ellipse(_hdc, disp_x - POINT_RADIUS, disp_y - POINT_RADIUS,
      disp_x + POINT_RADIUS, disp_y + POINT_RADIUS);
}

void GraphicWindow::ellipse(double x, double y, double ra, double rb,COLORREF mColor)
{
   SelectObject(_hdc, CreatePen(PS_SOLID,1,mColor));
   Ellipse(_hdc, user_to_disp_x(x - ra), user_to_disp_y(y - rb),
      user_to_disp_x(x + ra),user_to_disp_y(y + rb));
}
void GraphicWindow::ellipse(double x, double y, double ra, double rb, COLORREF mColor,int i)
{
	//SelectObject(_hdc, CreatePen(PS_SOLID, 1, RGB(255,255,255)));
	HBRUSH hBrush;
	hBrush =(HBRUSH)GetStockObject(GRAY_BRUSH);
	SelectObject(_hdc, hBrush);
	Ellipse(_hdc, user_to_disp_x(x - ra), user_to_disp_y(y - rb),
		user_to_disp_x(x + ra), user_to_disp_y(y + rb));

}
void GraphicWindow::line(double xfrom,double yfrom,double xto,double yto,COLORREF mColor)
{  
   SelectObject(_hdc, CreatePen(PS_SOLID,2,mColor));
   MoveToEx(_hdc, user_to_disp_x(xfrom), user_to_disp_y(yfrom), 0);
   LineTo(_hdc,user_to_disp_x(xto), user_to_disp_y(yto));
}

void GraphicWindow::text(string s,double x,double y)
{
	
   const char* t = s.c_str();
   SetBkMode(_hdc,TRANSPARENT);
   SetTextColor(_hdc, RGB(255, 255, 0));
   TextOut(_hdc, user_to_disp_x(x), user_to_disp_y(y), t, lstrlen(t));


}

GraphicWindow& GraphicWindow::operator<<(Point p)//重载运算符。所以可以直接cwin<<
{  
	point(p.get_x(), p.get_y(),p.get_color());
   return *this;
}

GraphicWindow& GraphicWindow::operator<<(Circle c)
{  
	ellipse(c.get_center().get_x(), c.get_center().get_y(), c.get_radius(), c.get_radius(),c.get_color(),1);
   return *this;
}

GraphicWindow& GraphicWindow::operator<<(Line s)
{  
	line(s.get_start().get_x(), s.get_start().get_y(), s.get_end().get_x(), s.get_end().get_y(),s.get_color());
   return *this;
}

GraphicWindow& GraphicWindow::operator<<(Message t)
{  
   text(t.get_text(), t.get_start().get_x(), t.get_start().get_y());
   return *this;
}
