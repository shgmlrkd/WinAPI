#include "Framework.h"

PaintTool::PaintTool(HWND hWnd)
{
	hdc = GetDC(hWnd);	

	hPens = new HPEN[PEN_SIZE];

	hPens[0] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	hPens[1] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	hPens[2] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
}

PaintTool::~PaintTool()
{	
	for (int i = 0; i < PEN_SIZE; i++)
	{
		DeleteObject(hPens[i]);
	}

	delete[] hPens;
}

void PaintTool::OnMouseMove(LPARAM lParam)
{
	if (!isMouseDown) return;

	curMousePos.x = LOWORD(lParam);
	curMousePos.y = HIWORD(lParam);

	MoveToEx(hdc, prevMousePos.x, prevMousePos.y, nullptr);
	LineTo(hdc, curMousePos.x, curMousePos.y);

	prevMousePos = curMousePos;
}

void PaintTool::OnLButtonDown(LPARAM lParam)
{
	prevMousePos.x = LOWORD(lParam);
	prevMousePos.y = HIWORD(lParam);
	isMouseDown = true;

	
}

void PaintTool::OnLButtonUp(LPARAM lParam)
{
	isMouseDown = false;	
}

void PaintTool::OnKeyDown(WPARAM wParam)
{
	//switch (wParam)
	//{
	//case '1':
	//	SelectObject(hdc, hPens[0]);
	//	break;		
	//default:
	//	break;
	//}

	int index = wParam - '1';

	if (index < 0 || index >= PEN_SIZE) return;

	SelectObject(hdc, hPens[index]);
}
