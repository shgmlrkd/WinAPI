#include "Framework.h"

Player::Player() : Circle(50)
{
}

Player::~Player()
{
}

void Player::Update()
{
	if (GetAsyncKeyState(VK_RIGHT))
		center.x += SPEED;
	if (GetAsyncKeyState(VK_LEFT))
		center.x -= SPEED;
	if (GetAsyncKeyState(VK_UP))
		center.y -= SPEED;
	if (GetAsyncKeyState(VK_DOWN))
		center.y += SPEED;

	InvalidateRect(hWnd, nullptr, true);
}
