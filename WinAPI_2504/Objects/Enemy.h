#pragma once

class Enemy : public Circle
{
public:
	Enemy();
	~Enemy();

	void Update();
	void Render(HDC hdc);

private:
	int hp = 100;

	HBRUSH hRedBrush;
	HBRUSH hBlueBrush;
	HBRUSH hSelectBrush;
};