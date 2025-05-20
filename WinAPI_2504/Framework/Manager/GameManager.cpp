#include "Framework.h"

<<<<<<< HEAD
#include "Scenes/ShootingScene.h"
#include "Scenes/TitleScene.h"
#include "Scenes/InventoryScene.h"

GameManager::GameManager()
{
	hdc = GetDC(hWnd);	

	backBufferDC = CreateCompatibleDC(hdc);
	backBufferBitmap = CreateCompatibleBitmap(hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
	SelectObject(backBufferDC, backBufferBitmap);	

	SetBkMode(backBufferDC, TRANSPARENT);

	Create();

	SCENE->AddScene("Title", new TitleScene());
	SCENE->AddScene("Game", new ShootingScene());
	SCENE->AddScene("Inven", new InventoryScene());

	SCENE->ChangeScene("Title");
=======
#include "Scenes/TutorialScene.h"

GameManager::GameManager()
{
	Create();
		
	SCENE->AddScene("Game", new TutorialScene());	

	SCENE->ChangeScene("Game");
>>>>>>> upstream/main
}

GameManager::~GameManager()
{
<<<<<<< HEAD
	ReleaseDC(hWnd, hdc);			

	Release();

	DeleteObject(backBufferBitmap);
	DeleteDC(backBufferDC);
=======
	Release();
>>>>>>> upstream/main
}

void GameManager::Update()
{
	Timer::Get()->Update();
	Input::Get()->Update();

	SCENE->Update();

	InvalidateRect(hWnd, nullptr, false);
}

void GameManager::Render()
{
<<<<<<< HEAD
	PatBlt(backBufferDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITENESS);	

	SCENE->Render(backBufferDC);
	Timer::Get()->Render(backBufferDC);

	BitBlt(hdc, 
		0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
		backBufferDC, 0, 0, SRCCOPY);
=======
	Device::Get()->Clear();

	SCENE->Render();	

	Device::Get()->Present();
>>>>>>> upstream/main
}

void GameManager::Create()
{
	Timer::Get();
	Input::Get();
<<<<<<< HEAD
=======

	Device::Get();

>>>>>>> upstream/main
	SceneManager::Get();
}

void GameManager::Release()
{
	Timer::Delete();
	Input::Delete();

<<<<<<< HEAD
=======
	Device::Delete();
	Shader::Delete();

>>>>>>> upstream/main
	SceneManager::Delete();
}
