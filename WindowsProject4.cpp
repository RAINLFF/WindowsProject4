//WindowsProject4.cpp: 定义应用程序的入口点。
//

#include "stdafx.h"
#include "WindowsProject4.h"
#include"stdlib.h"
#include"time.h"
#include"stdio.h"
#include"string.h"
#define MAX_LOADSTRING 100
#define MaxSize 5
#pragma warning(disable:4996)			//无视警告
typedef struct
{
	int number[MaxSize];
	int  top;
}Stack;
void NewTurnUp(int Game[4][4]);
void NewTurnDown(int Game[4][4]);
void NewTurnRight(int Game[4][4]);
void NewTurnLeft(int Game[4][4]);
void InitStack(Stack *&s);
void Push(Stack *&s, int n);
int Pop(Stack *&s);
int GetTop(Stack *&s);
int Game[4][4] = { 0 };					//利用一个数组来储存游戏中的数字
void turn_down(int  Game[4][4]);		//向下操作
void turn_up(int Game[4][4]);			//向上操作
void turn_left(int Game[4][4]);			//向左操作
void turn_right(int Game[4][4]);		//向右操作
bool Judge(int Game[4][4]);				//判断游戏是否能够结束
bool JudgeZero(int Game[4][4]);			//判断是否还有为0的数字
void btn_change();						//对按钮实行sendmessage操作使按钮的文本改变
void RandomNumber(int Game[4][4]);		//生成一个依据时间的随机数
int Score(int Game[4][4]);				//计算总分数
bool StackEmpty(Stack *&s);				//判断栈是否为空
FILE *fp;								//定义全局文件变量，实现存储读取功能
										// 全局变量: 
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
												/*按钮的句柄变量*/
HWND ScoreHWnd,
btn_00,
btn_01,
btn_02,
btn_03,
btn_10,
btn_11,
btn_12,
btn_13,
btn_20,
btn_21,
btn_22,
btn_23,
btn_30,
btn_31,
btn_32,
btn_33;		//定义按钮的句柄，以便后面进行sendmessage操作.
			// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DigProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 在此放置代码。
	/****************2048游戏部分代码******************/
	srand((unsigned int)time(NULL));		//让程序更加随机
	int i, j;
	j = rand() % 4;
	i = rand() % 4;
	Game[i][j] = (rand() % 2 + 1) * 2;	//初始化数组中第一个数字
										/****************2048游戏部分代码******************/
										// 初始化全局字符串
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WINDOWSPROJECT4, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT4));

	MSG msg;

	// 主消息循环: 
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(255, 192, 203));
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WINDOWSPROJECT4);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON3));

	return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 将实例句柄存储在全局变量中

	HWND hWnd = CreateWindowW(szWindowClass, L"冯桂璠的2048", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 350, 450, nullptr, nullptr, hInstance, nullptr);   //创建主窗口

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{


	switch (message)
	{

	case WM_CREATE:
	{


		CreateWindow(L"Static", L"2048", SS_LEFT | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 50, 50, 33, 20, hWnd, NULL, hInst, NULL);
		CreateWindow(L"Static", L"得分:", SS_LEFT | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 150, 50, 40, 20, hWnd, NULL, hInst, NULL);
		ScoreHWnd = CreateWindow(L"Static", L"", SS_LEFT | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 190, 50, 70, 20, hWnd, NULL, hInst, NULL);
		btn_00 = CreateWindow(L"Button", L"", SS_LEFT | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 40, 110, 60, 60, hWnd, (HMENU)100, hInst, NULL);
		btn_01 = CreateWindow(L"Button", L"", SS_LEFT | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 100, 110, 60, 60, hWnd, (HMENU)100, hInst, NULL);
		btn_02 = CreateWindow(L"Button", L"", SS_LEFT | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 160, 110, 60, 60, hWnd, (HMENU)100, hInst, NULL);
		btn_03 = CreateWindow(L"Button", L"", SS_LEFT | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 220, 110, 60, 60, hWnd, (HMENU)100, hInst, NULL);
		btn_10 = CreateWindow(L"Button", L"", SS_LEFT | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 40, 170, 60, 60, hWnd, (HMENU)100, hInst, NULL);
		btn_11 = CreateWindow(L"Button", L"", SS_LEFT | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 100, 170, 60, 60, hWnd, (HMENU)100, hInst, NULL);
		btn_12 = CreateWindow(L"Button", L"", SS_LEFT | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 160, 170, 60, 60, hWnd, (HMENU)100, hInst, NULL);
		btn_13 = CreateWindow(L"Button", L"", SS_LEFT | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 220, 170, 60, 60, hWnd, (HMENU)100, hInst, NULL);
		btn_20 = CreateWindow(L"Button", L"", SS_LEFT | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 40, 230, 60, 60, hWnd, (HMENU)100, hInst, NULL);
		btn_21 = CreateWindow(L"Button", L"", SS_LEFT | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 100, 230, 60, 60, hWnd, (HMENU)100, hInst, NULL);
		btn_22 = CreateWindow(L"Button", L"", SS_LEFT | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 160, 230, 60, 60, hWnd, (HMENU)100, hInst, NULL);
		btn_23 = CreateWindow(L"Button", L"", SS_LEFT | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 220, 230, 60, 60, hWnd, (HMENU)100, hInst, NULL);
		btn_30 = CreateWindow(L"Button", L"", SS_LEFT | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 40, 290, 60, 60, hWnd, (HMENU)100, hInst, NULL);
		btn_31 = CreateWindow(L"Button", L"", SS_LEFT | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 100, 290, 60, 60, hWnd, (HMENU)100, hInst, NULL);
		btn_32 = CreateWindow(L"Button", L"", SS_LEFT | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 160, 290, 60, 60, hWnd, (HMENU)100, hInst, NULL);
		btn_33 = CreateWindow(L"Button", L"", SS_LEFT | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 220, 290, 60, 60, hWnd, (HMENU)100, hInst, NULL);
		btn_change();


	}
	return 0;
	case WM_KEYDOWN:     //检测键盘按下消息
	{
		if (VK_UP == wParam)
		{
			NewTurnUp(Game);
			RandomNumber(Game);
			btn_change();
			if (Judge(Game) == 0)
				MessageBox(hWnd, L"游戏结束", L"", MB_OK);
		}
		if (VK_DOWN == wParam)
		{
			NewTurnDown(Game);
			RandomNumber(Game);
			btn_change();
			if (Judge(Game) == 0)
				MessageBox(hWnd, L"游戏结束", L"", MB_OK);

		}
		if (VK_LEFT == wParam)
		{
			NewTurnLeft(Game);
			RandomNumber(Game);
			btn_change();
			if (Judge(Game) == 0)
				MessageBox(hWnd, L"游戏结束", L"", MB_OK);

		}
		if (VK_RIGHT == wParam)
		{
			NewTurnRight(Game);
			RandomNumber(Game);
			btn_change();
			if (Judge(Game) == 0)
				MessageBox(hWnd, L"游戏结束", L"哎呀", MB_OK);

		}
	}
	return 0;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 分析菜单选择: 

		switch (wmId)
		{
		case IDM_UP:
		{
			turn_up(Game);
			RandomNumber(Game);
			btn_change();
			if (Judge(Game) == 0)
				MessageBox(hWnd, L"游戏结束", L"", MB_OK);
		}
		break;
		case IDM_DOWN:
		{
			turn_down(Game);
			RandomNumber(Game);
			btn_change();
			if (Judge(Game) == 0)
				MessageBox(hWnd, L"游戏结束", L"", MB_OK);
		}
		break;
		case IDM_LEFT:
		{
			turn_left(Game);
			RandomNumber(Game);
			btn_change();
			if (Judge(Game) == 0)
				MessageBox(hWnd, L"游戏结束", L"", MB_OK);
		}
		break;
		case IDM_RIGHT:
		{
			turn_right(Game);
			RandomNumber(Game);
			btn_change();
			if (Judge(Game) == 0)
				MessageBox(hWnd, L"游戏结束", L"", MB_OK);
		}
		break;
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DigProc);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_SAVED1:
			fp = fopen(".\\SAVE1.txt", "w");
			for (int i = 0; i<4; i++)
				for (int j = 0; j<4; j++)
					fprintf(fp, "%d\n", Game[i][j]);
			fclose(fp);
			MessageBox(hWnd, L"已经存好啦", L"(＾Ｕ＾)ノ", MB_OK);

			break;
		case IDM_SAVED2:
			fp = fopen(".\\SAVE2.txt", "w");
			for (int i = 0; i<4; i++)
				for (int j = 0; j<4; j++)
					fprintf(fp, "%d\n", Game[i][j]);
			fclose(fp);
			MessageBox(hWnd, L"已经存好啦", L"(＾Ｕ＾)ノ", MB_OK);
			break;
		case IDM_LOAD1:
			fp = fopen(".\\SAVE1.txt", "r");
			if (fp == NULL)
			{
				MessageBox(hWnd, L"没有这个存档", L"哎呀", MB_OK);

			}
			else
			{
				for (int i = 0; i < 4; i++)
					for (int j = 0; j < 4; j++)
						fscanf(fp, "%d", &Game[i][j]);
				MessageBox(hWnd, L"读取成功", L"嘿嘿", MB_OK);
				fclose(fp);
				btn_change();
			}
			break;
		case IDM_LOAD2:
			fp = fopen(".\\SAVE2.txt", "r");
			if (fp == NULL)
			{
				MessageBox(hWnd, L"读取成功", L"嘿嘿", MB_OK);

			}
			else
			{
				for (int i = 0; i < 4; i++)
					for (int j = 0; j < 4; j++)
						fscanf(fp, "%d", &Game[i][j]);
				fclose(fp);
				btn_change();
			}
			break;

		case IDM_REST:
			int i, j;
			for (i = 0; i < 4; i++)
				for (j = 0; j < 4; j++)
					Game[i][j] = 0;
			srand((unsigned int)time(NULL));
			j = rand() % 4;
			i = rand() % 4;
			Game[i][j] = (rand() % 2 + 1) * 2;
			btn_change();
			break;
		case 100:
			MessageBox(hWnd, L"这是个按钮。别点了", L"", MB_OK);
			break;
		default:
			break;
		}
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
BOOL CALLBACK DigProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) //响应对话框(dialog)
{
	static HBITMAP hbitmap;//位图句柄
	BITMAP bitmap;

	if (message == WM_INITDIALOG)//初始化对话框
	{
		hbitmap = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
		GetObject(hbitmap, sizeof(bitmap), &bitmap);
		return true;
	}
	if (message == WM_CLOSE)
	{
		EndDialog(hDlg, 0); //0返回值
		return true;
	}
	if (message == WM_PAINT)
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hDlg, &ps);

		HDC hdcMem = CreateCompatibleDC(hdc);//内存   兼容内存DC

		SelectObject(hdcMem, hbitmap); //将位图对象选进内存DC
		BitBlt(hdc, 0, 0, 500, 500, hdcMem, 0, 0, SRCCOPY);// 将位图对象从内存DC传送到对话框DC
		DeleteObject(hbitmap);
		DeleteDC(hdcMem);
		EndPaint(hDlg, &ps);
		return true;
	}
	return false;
}
/***************************2048函数部分**************************/
void turn_down(int  Game[4][4])
{
	int i, j, n, n2, count = 0;
	int temp[4];
	for (i = 0; i < 4; i++)
	{
		for (j = 3; j >= 0; j--)
		{
			if (Game[j][i] != 0)
			{
				temp[count] = Game[j][i];  // 把某行中所有非数字存入temp中
				count++;					//存完后count的数值为非零数字的个数
			}
		}



		//此时temp中已存入所有数字
		if (count > 1)					//如果temp中只有一个数字，不需要整合
			for (n = 0; n < count - 1; n++)		//遍历所有数字
			{
				if (temp[n] == temp[n + 1])
				{
					temp[n] = temp[n] * 2;
					if (n == count - 2)   //当n+1为最后一个元素时，直接count-1即可
					{
						count = count - 1;
						break;
					}
					n2 = n + 1;
					for (n2; n2 < count - 1; n2++)
						temp[n2] = temp[n2 + 1];
					count = count - 1;

				}

			}



		for (j = 0; j < 4; j++)	//对整列清零。
			Game[j][i] = 0;
		j = 4 - count;
		while (count > 0)
		{
			Game[j][i] = temp[count - 1];
			count--;
			j++;
		}


	}
}
void turn_up(int Game[4][4])
{
	int i, j, n, n2, count = 0;
	int temp[4];
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j <= 3; j++)
		{
			if (Game[j][i] != 0)
			{
				temp[count] = Game[j][i];  // 把某行中所有非数字存入temp中
				count++;					//存完后count的数值为非零数字的个数
			}
		}



		//此时temp中已存入所有数字
		if (count > 1)					//如果temp中只有一个数字，不需要整合
			for (n = 0; n < count - 1; n++)		//遍历所有数字
			{
				if (temp[n] == temp[n + 1])
				{
					temp[n] = temp[n] * 2;
					if (n == count - 2)   //当n+1为最后一个元素时，直接count-1即可
					{
						count = count - 1;
						break;
					}
					n2 = n + 1;
					for (n2; n2 < count - 1; n2++)
						temp[n2] = temp[n2 + 1];
					count = count - 1;

				}

			}


		for (j = 0; j < 4; j++)	//对整列清零。
			Game[j][i] = 0;
		j = count - 1;
		while (count > 0)
		{
			Game[j][i] = temp[count - 1];
			count--;
			j--;
		}


	}
}
void turn_left(int Game[4][4])
{
	int i, j, n, n2, count = 0;
	int temp[4];
	for (j = 0; j < 4; j++)
	{
		for (i = 0; i <= 3; i++)
		{
			if (Game[j][i] != 0)
			{
				temp[count] = Game[j][i];  // 把某行中所有非数字存入temp中
				count++;					//存完后count的数值为非零数字的个数
			}
		}



		//此时temp中已存入所有数字
		if (count > 1)					//如果temp中只有一个数字，不需要整合
			for (n = 0; n < count - 1; n++)		//遍历所有数字
			{
				if (temp[n] == temp[n + 1])
				{
					temp[n] = temp[n] * 2;
					if (n == count - 2)   //当n+1为最后一个元素时，直接count-1即可
					{
						count = count - 1;
						break;
					}
					n2 = n + 1;
					for (n2; n2 < count - 1; n2++)
						temp[n2] = temp[n2 + 1];
					count = count - 1;

				}

			}



		for (i = 0; i < 4; i++)	//对整列清零。
			Game[j][i] = 0;
		i = count - 1;
		while (count > 0)
		{
			Game[j][i] = temp[count - 1];
			count--;
			i--;
		}


	}
}
void turn_right(int Game[4][4])
{
	int i, j, n2;
	int count = 0;
	int temp[4];
	int n;
	for (j = 0; j < 4; j++)
	{
		for (i = 3; i >= 0; i--)
		{
			if (Game[j][i] != 0)
			{
				temp[count] = Game[j][i];  // 把某行中所有非数字存入temp中
				count++;					//存完后count的数值为非零数字的个数
			}
		}



		//此时temp中已存入所有数字
		if (count > 1)					//如果temp中只有一个数字，不需要整合
			for (n = 0; n < count - 1; n++)		//遍历所有数字
			{
				if (temp[n] == temp[n + 1])
				{
					temp[n] = temp[n] * 2;
					if (n == count - 2)   //当n+1为最后一个元素时，直接count-1即可
					{
						count = count - 1;
						break;
					}
					n2 = n + 1;
					for (n2; n2 < count - 1; n2++)
						temp[n2] = temp[n2 + 1];
					count = count - 1;

				}

			}


		for (i = 0; i < 4; i++)	//对整列清零。
			Game[j][i] = 0;
		i = 4 - count;
		while (count > 0)
		{
			Game[j][i] = temp[count - 1];
			count--;
			i++;
		}


	}
}
bool Judge(int Game[4][4])  //判断游戏是否还能继续
{
	int i, j;
	if (JudgeZero(Game))
		return true;
	else
	{
		for (i = 0; i < 4; i++)
			for (j = 0; j < 3; j++)
				if (Game[i][j] == Game[i][j + 1])
					return true;
		for (j = 0; j < 4; j++)
			for (i = 0; i < 3; i++)
				if (Game[i][j] == Game[i + 1][j])
					return true;
		return false;
	}
}
bool JudgeZero(int Game[4][4])
{
	int i, j;
	for (i = 0; i<4; i++)
		for (j = 0; j< 4; j++)
		{
			if (Game[i][j] == 0)
				return true;
		}
	return false;
}
void btn_change()
{

	static TCHAR Number_00[50], Number_01[50], Number_02[50], Number_03[50],
		Number_10[50], Number_11[50], Number_12[50], Number_13[50], Number_20[50],
		Number_21[50], Number_22[50], Number_23[50], Number_30[50], Number_31[50], Number_32[50], Number_33[50], LScore[50];
	int score = Score(Game);
	wsprintf(LScore, L"%d", score);
	wsprintf(Number_00, L"%d", Game[0][0]);									//将数值转化为TCHAR以便后续sendmessage
	wsprintf(Number_01, L"%d", Game[0][1]);
	wsprintf(Number_02, L"%d", Game[0][2]);
	wsprintf(Number_03, L"%d", Game[0][3]);
	wsprintf(Number_10, L"%d", Game[1][0]);
	wsprintf(Number_11, L"%d", Game[1][1]);
	wsprintf(Number_12, L"%d", Game[1][2]);
	wsprintf(Number_13, L"%d", Game[1][3]);
	wsprintf(Number_20, L"%d", Game[2][0]);
	wsprintf(Number_21, L"%d", Game[2][1]);
	wsprintf(Number_22, L"%d", Game[2][2]);
	wsprintf(Number_23, L"%d", Game[2][3]);
	wsprintf(Number_30, L"%d", Game[3][0]);
	wsprintf(Number_31, L"%d", Game[3][1]);
	wsprintf(Number_32, L"%d", Game[3][2]);
	wsprintf(Number_33, L"%d", Game[3][3]);
	SendMessage(ScoreHWnd, WM_SETTEXT, WPARAM(NULL), LPARAM(LScore));
	if (Game[0][0] == 0)
		SendMessage(btn_00, WM_SETTEXT, WPARAM(NULL), LPARAM(L""));
	else
		SendMessage(btn_00, WM_SETTEXT, WPARAM(NULL), LPARAM((Number_00)));
	if (Game[0][1] == 0)
		SendMessage(btn_01, WM_SETTEXT, WPARAM(NULL), LPARAM(L""));
	else
		SendMessage(btn_01, WM_SETTEXT, WPARAM(NULL), LPARAM((Number_01)));
	if (Game[0][2] == 0)
		SendMessage(btn_02, WM_SETTEXT, WPARAM(NULL), LPARAM(L""));
	else
		SendMessage(btn_02, WM_SETTEXT, WPARAM(NULL), LPARAM((Number_02)));
	if (Game[0][3] == 0)
		SendMessage(btn_03, WM_SETTEXT, WPARAM(NULL), LPARAM(L""));
	else
		SendMessage(btn_03, WM_SETTEXT, WPARAM(NULL), LPARAM((Number_03)));
	if (Game[1][0] == 0)
		SendMessage(btn_10, WM_SETTEXT, WPARAM(NULL), LPARAM(L""));
	else
		SendMessage(btn_10, WM_SETTEXT, WPARAM(NULL), LPARAM((Number_10)));
	if (Game[1][1] == 0)
		SendMessage(btn_11, WM_SETTEXT, WPARAM(NULL), LPARAM(L""));
	else
		SendMessage(btn_11, WM_SETTEXT, WPARAM(NULL), LPARAM((Number_11)));
	if (Game[1][2] == 0)
		SendMessage(btn_12, WM_SETTEXT, WPARAM(NULL), LPARAM(L""));
	else
		SendMessage(btn_12, WM_SETTEXT, WPARAM(NULL), LPARAM((Number_12)));
	if (Game[1][3] == 0)
		SendMessage(btn_13, WM_SETTEXT, WPARAM(NULL), LPARAM(L""));
	else
		SendMessage(btn_13, WM_SETTEXT, WPARAM(NULL), LPARAM((Number_13)));
	if (Game[2][0] == 0)
		SendMessage(btn_20, WM_SETTEXT, WPARAM(NULL), LPARAM(L""));
	else
		SendMessage(btn_20, WM_SETTEXT, WPARAM(NULL), LPARAM((Number_20)));
	if (Game[2][1] == 0)
		SendMessage(btn_21, WM_SETTEXT, WPARAM(NULL), LPARAM(L""));
	else
		SendMessage(btn_21, WM_SETTEXT, WPARAM(NULL), LPARAM((Number_21)));
	if (Game[2][2] == 0)
		SendMessage(btn_22, WM_SETTEXT, WPARAM(NULL), LPARAM(L""));
	else
		SendMessage(btn_22, WM_SETTEXT, WPARAM(NULL), LPARAM((Number_22)));
	if (Game[2][3] == 0)
		SendMessage(btn_23, WM_SETTEXT, WPARAM(NULL), LPARAM(L""));
	else
		SendMessage(btn_23, WM_SETTEXT, WPARAM(NULL), LPARAM((Number_23)));
	if (Game[3][0] == 0)
		SendMessage(btn_30, WM_SETTEXT, WPARAM(NULL), LPARAM(L""));
	else
		SendMessage(btn_30, WM_SETTEXT, WPARAM(NULL), LPARAM((Number_30)));
	if (Game[3][1] == 0)
		SendMessage(btn_31, WM_SETTEXT, WPARAM(NULL), LPARAM(L""));
	else
		SendMessage(btn_31, WM_SETTEXT, WPARAM(NULL), LPARAM((Number_31)));
	if (Game[3][2] == 0)
		SendMessage(btn_32, WM_SETTEXT, WPARAM(NULL), LPARAM(L""));
	else
		SendMessage(btn_32, WM_SETTEXT, WPARAM(NULL), LPARAM((Number_32)));
	if (Game[3][3] == 0)
		SendMessage(btn_33, WM_SETTEXT, WPARAM(NULL), LPARAM(L""));
	else
		SendMessage(btn_33, WM_SETTEXT, WPARAM(NULL), LPARAM((Number_33)));
}
void RandomNumber(int Game[4][4])
{
	int flag = 0;
	int i, j;
	if (Judge(Game))
		if (JudgeZero(Game))
		{
			while (flag == 0)
			{
				j = rand() % 4;
				i = rand() % 4;
				if (Game[j][i] == 0) {
					Game[j][i] = (rand() % 2 + 1) * 2;
					flag = 1;
				}
			}
		}

}
int Score(int Game[4][4])
{
	int i, j;
	int count = 0;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
			count = count + Game[i][j];
	return count;
}
void InitStack(Stack *&s)
{
	s = (Stack *)malloc(sizeof(Stack));
	s->top = -1;
}
void Push(Stack *&s, int n)
{
	s->top++;
	s->number[s->top] = n;
}
int Pop(Stack *&s)
{
	int n;
	s->top--;
	n = s->number[s->top + 1];
	return n;
}
int GetTop(Stack *&s)
{
	return s->number[s->top];
}
bool StackEmpty(Stack *&s)
{
	return s->top == -1;
}
void NewTurnDown(int Game[4][4])
{
	Stack *s;
	InitStack(s);
	int i, j, number, flag = 0;
	for (i = 0; i < 4; i++)
	{

		for (j = 3; j >= 0; j--)
		{
			if (Game[j][i] != 0)
				if (flag == 1)
				{
					Push(s, Game[j][i]);
					flag = 0;
				}
				else
				{
					if (StackEmpty(s))
						Push(s, Game[j][i]);
					else
					{
						if (Game[j][i] == GetTop(s))
						{
							s->number[s->top] = s->number[s->top] * 2;
							flag = 1;
						}
						else
							Push(s, Game[j][i]);
					}
				}
		}

		for (j = 0; j < 4; j++)	//对整列清零。
			Game[j][i] = 0;
		j = 3 - s->top;
		while (j < 4)
		{
			Game[j][i] = Pop(s);
			j++;
		}
		s->top = -1;
	}
	free(s);
}
void NewTurnUp(int Game[4][4])
{
	Stack *s;
	InitStack(s);
	int i, j, n, number, flag = 0;
	for (i = 0; i < 4; i++)
	{

		for (j = 0; j < 4; j++)
		{
			if (Game[j][i] != 0)
				if (flag == 1)
				{
					Push(s, Game[j][i]);
					flag = 0;
				}
				else
				{
					if (StackEmpty(s))
						Push(s, Game[j][i]);
					else
					{
						if (Game[j][i] == GetTop(s))
						{
							s->number[s->top] = s->number[s->top] * 2;
							flag = 1;
						}
						else
							Push(s, Game[j][i]);
					}
				}
		}

		for (j = 0; j < 4; j++)	//对整列清零。
			Game[j][i] = 0;
		j = s->top;
		while (j >= 0)
		{
			Game[j][i] = Pop(s);
			j--;
		}
		s->top = -1;
	}
	free(s);
}
void NewTurnRight(int Game[4][4])
{
	Stack *s;
	InitStack(s);
	int i, j, number, flag = 0;
	for (i = 0; i < 4; i++)
	{

		for (j = 3; j >= 0; j--)
		{
			if (Game[i][j] != 0)
				if (flag == 1)
				{
					Push(s, Game[i][j]);
					flag = 0;
				}
				else
				{
					if (StackEmpty(s))
						Push(s, Game[i][j]);
					else
					{
						if (Game[i][j] == GetTop(s))
						{
							s->number[s->top] = s->number[s->top] * 2;
							flag = 1;
						}
						else
							Push(s, Game[i][j]);
					}
				}
		}

		for (j = 0; j < 4; j++)	//对整列清零。
			Game[i][j] = 0;
		j = 3 - s->top;
		while (j < 4)
		{
			Game[i][j] = Pop(s);
			j++;
		}
		s->top = -1;
	}
	free(s);
}
void NewTurnLeft(int Game[4][4])
{
	Stack *s;
	InitStack(s);
	int i, j, n, number, flag = 0;
	for (i = 0; i < 4; i++)
	{

		for (j = 0; j < 4; j++)
		{
			if (Game[i][j] != 0)
				if (flag == 1)
				{
					Push(s, Game[i][j]);
					flag = 0;
				}
				else
				{
					if (StackEmpty(s))
						Push(s, Game[i][j]);
					else
					{
						if (Game[i][j] == GetTop(s))
						{
							s->number[s->top] = s->number[s->top] * 2;
							flag = 1;
						}
						else
							Push(s, Game[i][j]);
					}
				}
		}

		for (j = 0; j < 4; j++)	//对整列清零。
			Game[i][j] = 0;
		j = s->top;
		while (j >= 0)
		{
			Game[i][j] = Pop(s);
			j--;
		}
		s->top = -1;
	}
	free(s);
}