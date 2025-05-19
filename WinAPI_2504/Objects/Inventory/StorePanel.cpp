#include "Framework.h"
#include "StorePanel.h"

StorePanel::StorePanel()
	: Panel(Vector2(200, CENTER_Y), Vector2(400, 500), RGB(0, 255, 0))
{
	CreateGoods();	

	buyButton = new Button(Vector2(Left() + 50, Bottom() - 50), Vector2(100, 50));
	buyButton->SetText(L"Buy");
	buyButton->SetBrush(RGB(0, 255, 0), RGB(0, 200, 0), RGB(0, 150, 0));
	buyButton->SetEvent(bind(&StorePanel::BuyItem, this));
	
	sellButton = new Button(Vector2(Right() - 50, Bottom() - 50), Vector2(100, 50));
	sellButton->SetText(L"Sell");
	sellButton->SetBrush(RGB(255, 0, 0), RGB(200, 0, 0), RGB(150, 0, 0));
	sellButton->SetEvent(bind(&StorePanel::SellItem, this));
}

StorePanel::~StorePanel()
{
	delete buyButton;
	delete sellButton;

	for (Good* good : goods)
	{
		delete good;
	}
}

void StorePanel::Update()
{
	if (!isActive)
		return;

	if (Input::Get()->IsKeyDown(VK_F2))
	{
		BuyItem();
	}

	Panel::Update();

	for (Good* good : goods)
	{
		good->Update();
	}

	buyButton->Update();
	sellButton->Update();
}

void StorePanel::Render(HDC hdc)
{
	if (!isActive)
		return;

	Panel::Render(hdc);

	for (Good* good : goods)
	{
		good->Render(hdc);
	}

	if (selectedGood)
	{
		string text = "SelectItem : " + selectedGood->GetItemData().name;
		TextOutA(hdc, Left(), Bottom(), text.c_str(), text.length());
	}

	buyButton->Render(hdc);
	sellButton->Render(hdc);

	string goldText = "Gold : " + to_string(InventoryPlayer::Get()->GetGold());
	TextOutA(hdc, Left(), Bottom() + 20, goldText.c_str(), goldText.length());
}

void StorePanel::CreateGoods()
{
	int itemCount = DataManager::Get()->GetItemCount();

	for (int i = 0; i < itemCount; i++)
	{
		ItemData itemData = DataManager::Get()->GetItem(1000 + i + 1);
		Vector2 pos;
		pos.x = center.x;
		pos.y = Top() + 50 + i * 100;

		Good* good = new Good(pos, itemData);
		good->SetObjectEvent(bind(&StorePanel::OnClickGood, this, placeholders::_1));
		good->SetObjectParameter(good);
		goods.push_back(good);
	}
}

void StorePanel::BuyItem()
{
	if (selectedGood == nullptr)
		return;

	//EventManager::Get()->ExcuteEvent("AddItem", selectedGood);
	//inventoryPanel->AddItem(selectedGood);
	InventoryPlayer::Get()->AddItem(selectedGood);
}

void StorePanel::SellItem()
{
	InventoryPlayer::Get()->RemoveItem();
}

void StorePanel::OnClickGood(void* good)
{
	selectedGood = (Good*)good;	
}
