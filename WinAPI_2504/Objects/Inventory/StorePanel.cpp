#include "Framework.h"
#include "StorePanel.h"

StorePanel::StorePanel()
	: Panel(CENTER, Vector2(400, 500), RGB(0, 255, 0))
{
	CreateGoods();
}

StorePanel::~StorePanel()
{
}

void StorePanel::Update()
{
	if (!isActive)
		return;

	Panel::Update();

	for (Good* good : goods)
	{
		good->Update();
	}
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

void StorePanel::OnClickGood(void* good)
{
	selectedGood = (Good*)good;	
}
