#pragma once

class PaintTool
{
private:
	const int PEN_SIZE = 3;

public:
	PaintTool(HWND hWnd);
	~PaintTool();	

	void OnMouseMove(LPARAM lParam);
	void OnLButtonDown(LPARAM lParam);
	void OnLButtonUp(LPARAM lParam);

	void OnKeyDown(WPARAM wParam);

private:
	HDC hdc;

	POINT prevMousePos = {};
	POINT curMousePos = {};

	bool isMouseDown = false;

	HPEN* hPens;
	HBRUSH* hBrushes;
};