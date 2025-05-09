#include "Framework.h"
#include "ShootingScene.h"

ShootingScene::ShootingScene()
{
	
}

ShootingScene::~ShootingScene()
{	
	
}

void ShootingScene::Update()
{
	if (Input::Get()->IsKeyDown(VK_F2))
	{
		SCENE->ChangeScene("Title");
	}

	player->Update();

	BulletManager::Get()->Update();
	EnemyManager::Get()->Update();
}

void ShootingScene::Render(HDC hdc)
{
	player->Render(hdc);

	BulletManager::Get()->Render(hdc);
	EnemyManager::Get()->Render(hdc);
}

void ShootingScene::Start()
{
	player = new Player();

	BulletManager::Get();
	EnemyManager::Get()->SetPlayer(player);
}

void ShootingScene::End()
{
	delete player;

	BulletManager::Delete();
	EnemyManager::Delete();
}
