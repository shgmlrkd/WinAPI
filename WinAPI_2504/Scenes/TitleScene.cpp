#include "Framework.h"
#include "TitleScene.h"

TitleScene::TitleScene()
{
	startButton = new Button(Vector2(300, 400), Vector2(200, 100));
	startButton->SetText(L"Start");
	startButton->SetBrush(RGB(0, 255, 0), RGB(0, 200, 0), RGB(0, 150, 0));
	startButton->SetEvent(bind(&TitleScene::OnClickStart, this));

	exitButton = new Button(Vector2(300, 600), Vector2(200, 100));
	exitButton->SetBrush(RGB(255, 0, 0), RGB(200, 0, 0), RGB(150, 0, 0));
	exitButton->SetText(L"Exit");
	exitButton->SetEvent(bind(&TitleScene::OnClickExit, this));
}

TitleScene::~TitleScene()
{
	delete startButton;
	delete exitButton;
}

void TitleScene::Update()
{
	if (Input::Get()->IsKeyDown(VK_F1))
	{
		SCENE->ChangeScene("Inven");
	}

	startButton->Update();
	exitButton->Update();
}

void TitleScene::Render(HDC hdc)
{
	TextOut(hdc, 100, 100, L"Title Scene", 12);

	startButton->Render(hdc);
	exitButton->Render(hdc);
}

void TitleScene::OnClickStart()
{
	SCENE->ChangeScene("Inven");
}

void TitleScene::OnClickExit()
{
	PostQuitMessage(0);
}
