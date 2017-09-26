#include "ctime"
#include "cmath"
#include "cstdlib"
#include "fig.h"
#include "ccc_win.h"
#include "Resource.h"
#define PI 3.1415926
void mclock(void);
void DrawTriangle();
void ShowMessage(int keyid);
int ccc_win_main(int menuId)
{
	switch (menuId)
	{
	case IDM_FIG1:
		mclock(); // 绘制时钟
		break;
	case IDM_FIG2:		
		DrawTriangle(); // 其它绘图程序
		break;
	default :
		ShowMessage(menuId);
	}



	return 0;
}

void mclock()
{
	Shape *pShape;

	cwin << Message(Point(-1, 7), "会动时钟");

	/* 画表盘 */
	int radius = 6;
	Point org(0, 0);

	pShape = &org;
	pShape->SetColor(RGB(255, 255, 255)); // 白色
	cwin << org;

	Circle clkPlate(org, radius);
	pShape = &clkPlate;
	pShape->SetColor(RGB(0, 0, 255));	// 蓝色
	cwin << clkPlate;

	double x, y, x_s, y_s, x_m, y_m, x_h, y_h;
	int i;
	for (i = 0; i<12; i++)
	{
		x = 0.9*radius*sin(PI*i / 6);
		y = 0.9*radius*cos(PI*i / 6);

		Point mPoint(x, y);
		pShape = &mPoint;
		pShape->SetColor((RGB(255, 255, 255)));
		cwin << mPoint;
	}

	/* 画表针 */
	struct tm local;
	time_t t;

	// 获取系统日历时间
	t = time(NULL);

	// 将日历时间转化为本地时间
	localtime_s(&local, &t);

	x_s = 0.89*radius*sin(PI*(local.tm_sec) / 30);
	y_s = 0.89*radius*cos(PI*(local.tm_sec) / 30);

	x_m = 0.7*radius*sin(PI*(local.tm_min) / 30);
	y_m = 0.7*radius*cos(PI*(local.tm_min) / 30);

	x_h = 0.5*radius*sin(PI*(local.tm_hour) / 6);
	y_h = 0.5*radius*cos(PI*(local.tm_hour) / 6);

	Point hEnd(x_h, y_h), mEnd(x_m, y_m), sEnd(x_s, y_s);
	Line hLine(org, hEnd), mLine(org, mEnd), sLine(org, sEnd);

	hLine.SetColor((RGB(255, 0, 0)));		// 红色 
	mLine.SetColor((RGB(0, 255, 0)));		// 绿色
	sLine.SetColor((RGB(255, 255, 0)));	// 黄色
	cwin << hLine << mLine << sLine << org;
}
void DrawTriangle()
{
	cwin << Message(Point(-1, 7), "魔法阵");

	double radius2 = 3.5;
	Point org2(0, 1);
	Circle clkPlate2(org2, radius2);
	Shape *pShape2;
	pShape2 = &clkPlate2;
	pShape2->SetColor(RGB(0, 255, 255));	// 蓝色
	cwin << clkPlate2;
	double radius = 3.3;
	Point org(0, 1);
	Circle clkPlate(org, radius);
	Shape *pShape;
	pShape = &clkPlate;
	pShape->SetColor(RGB(0, 255, 255));	// 蓝色
	cwin << clkPlate;
	Point p[] = { Point(-3,-0.5),Point(-3,2.5),Point(0,4),
		Point(3,2.5),Point(3,-0.5),Point(0,-2),};
	Line lines[] = { Line(p[2], p[0]), Line(p[4], p[0]), Line(p[2], p[4]) };
	for (int i = 0; i < 3; i++)
	{
		lines[i].SetColor((RGB(255, 0, 0)));
		cwin << lines[i];
	}
	Line lines1[] = { Line(p[1], p[5]), Line(p[5], p[3]), Line(p[3], p[1]) };
	for (int i = 0; i < 3; i++)
	{
		lines1[i].SetColor((RGB(255, 0, 0)));
		cwin << lines1[i];
	}
	
}

void ShowMessage(int keyid)
{
	int mess = keyid - 0x30;
	cwin << Message(Point(-1, 7), mess);
}