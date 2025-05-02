#pragma once

class GameManager
{
public:
	GameManager(HWND hWnd);
	~GameManager();

	void Update();
	void Render(HDC hdc);

private:
	HDC hdc;

	Player* player;
	Enemy* enemy;
};