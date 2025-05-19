#include "Framework.h"
#include "InventoryScene.h"

InventoryScene::InventoryScene()
{
	DataManager::Get()->LoadData("Resources/Tables/ItemTable.csv");

	CreateButtons();
	CreatePanels();	
}

InventoryScene::~InventoryScene()
{
	for (Button* button : buttons)
	{
		delete button;
	}
	buttons.clear();
}

void InventoryScene::Update()
{
	for (Button* button : buttons)
		button->Update();

	for (Panel* panel : panels)
		panel->Update();
}

void InventoryScene::Render(HDC hdc)
{
	for (Button* button : buttons)
		button->Render(hdc);

	for (Panel* panel : panels)
		panel->Render(hdc);
}

void InventoryScene::CreateButtons()
{
	buttons.push_back(new Button(Vector2(100, 100), Vector2(100, 50)));
	buttons.push_back(new Button(Vector2(200, 100), Vector2(100, 50)));
	buttons.push_back(new Button(Vector2(300, 100), Vector2(100, 50)));
	buttons[(int)State::Store]->SetText(L"Store");
	buttons[(int)State::Inventory]->SetText(L"Inventory");
	buttons[(int)State::Equip]->SetText(L"Equip");

	buttons[(int)State::Store]->SetBrush(RGB(0, 255, 0), RGB(0, 200, 0), RGB(0, 150, 0));
	buttons[(int)State::Inventory]->SetBrush(RGB(0, 0, 255), RGB(0, 0, 200), RGB(0, 0, 150));
	buttons[(int)State::Equip]->SetBrush(RGB(255, 0, 0), RGB(200, 0, 0), RGB(150, 0, 0));

	for (int i = 0; i < (int)State::End; i++)
	{
		buttons[i]->SetIntEvent(bind(&InventoryScene::OnClickButton, this, placeholders::_1));
		buttons[i]->SetIntParameter(i);
	}

	//buttons[0]->SetEvent([]() { /* Store button event */ });
	//buttons[1]->SetEvent([]() { /* Inventory button event */ });
	//buttons[2]->SetEvent([]() { /* Equip button event */ });
}

void InventoryScene::CreatePanels()
{	
	Vector2 size(400, 300);

	 panels.push_back(new StorePanel());	 	 
	 panels.push_back(new InventoryPanel());
	 panels.push_back(new EquipPanel());

	 //StorePanel* storePanel = (StorePanel*)panels[(int)State::Store];
	 //InventoryPanel* inventoryPanel = (InventoryPanel*)panels[(int)State::Inventory];
	 //storePanel->SetInventoryPanel(inventoryPanel);

	 int count = 0;
	 for (Panel* panel : panels)
	 {
		 panel->SetActive(false);
		 panel->Translate(Vector2::Right() * size.x * count++);
	 }
}

void InventoryScene::OnClickButton(int index)
{
	panels[index]->SetActive(true);
}
