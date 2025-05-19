#include "Framework.h"

Good::Good(Vector2 center, ItemData itemData)
	: Button(center, Vector2(200, 100)), itemData(itemData)
{
	SetBrush(RGB(0, 0, 255), RGB(0, 0, 200), RGB(0, 0, 150));
}

Good::~Good()
{
}

void Good::Render(HDC hdc)
{
	Button::Render(hdc);

	string text = "Name : " + itemData.name;
	TextOutA(hdc, Left() + 10, Top() + 10, text.c_str(), text.length());
	text = "Explane : " + itemData.explane;
	TextOutA(hdc, Left() + 10, Top() + 30, text.c_str(), text.length());
	text = "Price : " + to_string(itemData.price);
	TextOutA(hdc, Left() + 10, Top() + 50, text.c_str(), text.length());

}
