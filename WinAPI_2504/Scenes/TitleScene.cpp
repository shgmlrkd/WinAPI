#include "Framework.h"
#include "TitleScene.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	if (Input::Get()->IsKeyDown(VK_F1))
	{
		SCENE->ChangeScene("Game");
	}
}

void TitleScene::Render(HDC hdc)
{
	TextOut(hdc, 100, 100, L"Title Scene", 12);
}
