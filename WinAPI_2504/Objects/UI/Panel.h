#pragma once

class Panel : public Rect
{
public:
	Panel(Vector2 center, Vector2 size, COLORREF color);
	~Panel();

	virtual void Update();
	virtual void Render(HDC hdc);	

private:
	void OnClickClose();

private:
	HBRUSH hBrush = nullptr;	

	Button* closeButton = nullptr;
};