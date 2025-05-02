#include "Framework.h"

Enemy::Enemy() : Circle(100)
{
	hRedBrush = CreateSolidBrush(RGB(255, 0, 0));
	hBlueBrush = CreateSolidBrush(RGB(0, 0, 255));
}

Enemy::~Enemy()
{
	DeleteObject(hRedBrush);
	DeleteObject(hBlueBrush);
}

void Enemy::Update()
{
	if (IsCollisionPoint(mousePos))
	{
		hSelectBrush = hRedBrush;
	}
	else
	{
		hSelectBrush = hBlueBrush;
	}

	if (BulletManager::Get()->IsCollision(this))
	{
		//isActive = false;
		hp -= 10;

		if (hp <= 0)
		{
			isActive = false;
		}
	}
}

void Enemy::Render(HDC hdc)
{
	SelectObject(hdc, hSelectBrush);

	Circle::Render(hdc);
}
