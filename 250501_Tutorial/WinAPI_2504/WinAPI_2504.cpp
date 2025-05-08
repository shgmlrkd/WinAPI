﻿// WinAPI_2504.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "WinAPI_2504.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINAPI2504, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINAPI2504));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINAPI2504));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WINAPI2504);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   WCHAR title[] = L"내 게임";

   HWND hWnd = CreateWindowW(szWindowClass, title, WS_OVERLAPPEDWINDOW,
	   100, 100,//시작 위치
	   500, 500,//창 크기
       nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

//HWND -> Window Handle
//messgae -> 메시지
//wParam -> 메시지에 대한 추가 정보(키보드 입력정보, 마우스 입력정보 등)
//lParam -> 메시지에 대한 추가 정보(마우스 위치)

PaintTool* paintTool = nullptr;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
	case WM_CREATE:
	{
		paintTool = new PaintTool(hWnd);
	}
	break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
			//H -> Handle
			//DC -> Device Context
            //HDC -> 출력을 하는 부분에도 모두 관여
            HDC hdc = BeginPaint(hWnd, &ps);

			const WCHAR* text = L"Hello, World!";

			//LPCWSTR -> Long Pointer to Constant Wide String
            TextOut(hdc, 0, 0, text, 13);

            //Point
            for (int i = 0; i < 100; i++)
            {
				for (int j = 0; j < 100; j++)
				{
					SetPixel(hdc, 100 + i, 100 + j, RGB(0, 0, 0));
				}
            }			

            //Line
			MoveToEx(hdc, 0, 100, nullptr);//시작점
			LineTo(hdc, 100, 200);//끝점

			//Rectangle
			Rectangle(hdc, 100, 0, 200, 100);

			//Ellipse
			Ellipse(hdc, 200, 0, 300, 100);

            EndPaint(hWnd, &ps);
        }
        break;
	case WM_LBUTTONDOWN://마우스 왼쪽 버튼 클릭
	{
        //prevMousePos.x = LOWORD(lParam);
		//prevMousePos.y = HIWORD(lParam);
        //
		//isMouseDown = true;
		paintTool->OnLButtonDown(lParam);
	}
        break;
    case WM_MOUSEMOVE:
    {
        //if (isMouseDown)
        //{
        //    POINT curMousePos;
        //    curMousePos.x = LOWORD(lParam);
        //    curMousePos.y = HIWORD(lParam);
        //
        //    HDC hdc = GetDC(hWnd);
        //
		//	MoveToEx(hdc, prevMousePos.x, prevMousePos.y, nullptr);
		//	LineTo(hdc, curMousePos.x, curMousePos.y);
		//	ReleaseDC(hWnd, hdc);
		//	prevMousePos = curMousePos;
        //}        
		paintTool->OnMouseMove(lParam);
    }
        break;
    case WM_LBUTTONUP:
    {
        //isMouseDown = false;
		paintTool->OnLButtonUp(lParam);
    }
        break;

    case WM_KEYDOWN:
    {
		paintTool->OnKeyDown(wParam);
    }
        break;
    case WM_DESTROY:
		delete paintTool;
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
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
