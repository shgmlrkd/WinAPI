#include "Framework.h"
#include "Panel.h"

Panel::Panel(Vector2 center, Vector2 size, COLORREF color)
	: Rect(center, size)
{
	hBrush = CreateSolidBrush(color);
	closeButton = new Button(Vector2(Right(), Top()), Vector2(30, 30));
	closeButton->SetText(L"X");
	closeButton->SetBrush(RGB(255, 0, 0), RGB(200, 0, 0), RGB(150, 0, 0));
	closeButton->SetEvent(bind(&Panel::OnClickClose, this));
}

Panel::~Panel()
{
	DeleteObject(hBrush);
	delete closeButton;
}

void Panel::Update()
{
	if (!isActive) return;
	
	closeButton->SetCenter(Right(), Top());
	closeButton->Update();
}

void Panel::Render(HDC hdc)
{
	if (!isActive) return;

	HBRUSH defaultBrush = (HBRUSH)SelectObject(hdc, hBrush);
	
	Rect::Render(hdc);

	SelectObject(hdc, defaultBrush);

	closeButton->Render(hdc);
}

void Panel::OnClickClose()
{
	isActive = false;
}
