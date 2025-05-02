#include "Framework.h"

GameManager::GameManager(HWND hWnd)
{
	hdc = GetDC(hWnd);

	player = new Player();
	player->SetCenter(200, 300);

	enemy = new Enemy();
	enemy->SetCenter(200, 100);

	BulletManager::Get();
}

GameManager::~GameManager()
{
	ReleaseDC(hWnd, hdc);	

	delete player;

	BulletManager::Delete();
}

void GameManager::Update()
{
	player->Update();
	enemy->Update();

	if (player->IsCollisionCircle(enemy))
	{
		enemy->SetActive(false);
	}

	BulletManager::Get()->Update();

	InvalidateRect(hWnd, nullptr, true);
}

void GameManager::Render(HDC hdc)
{
	player->Render(hdc);
	enemy->Render(hdc);

	BulletManager::Get()->Render(hdc);
}
