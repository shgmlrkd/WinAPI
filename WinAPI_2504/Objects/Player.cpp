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

	if (GetAsyncKeyState(VK_SPACE))
	{
		//if(isKeyPressed == false)
		if (!isKeyPressed)
		{
			isKeyPressed = true;
			//bullet->Fire(center);
			Fire();
		}		
	}
	else
	{
		isKeyPressed = false;
	}

	
}

void Player::Render(HDC hdc)
{
	Circle::Render(hdc);	
}

void Player::Fire()
{
	BulletManager::Get()->Fire(center);
}

