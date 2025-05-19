#include "Framework.h"

EquipPanel::EquipPanel()
	: Panel(Vector2(200, CENTER_Y), Vector2(400, 500), RGB(255, 0, 0))
{
	equipItems[ItemData::Weapon] = nullptr;
	equipItems[ItemData::Armor] = nullptr;

	EventManager::Get()->AddEvent("Equip",
		bind(&EquipPanel::OnEquipItem, this, placeholders::_1));
	EventManager::Get()->AddEvent("Unequip",
		bind(&EquipPanel::OnUnequipItem, this, placeholders::_1));
}

EquipPanel::~EquipPanel()
{
}

void EquipPanel::Update()
{
	if (!isActive) return;

	Panel::Update();
	
}

void EquipPanel::Render(HDC hdc)
{
	if (!isActive) return;

	Panel::Render(hdc);

	Vector2 pos(Left() + 50, Top() + 50);

	for (pair<ItemData::Type, InventoryItem*> item : equipItems)
	{
		pos += Vector2::Down() * 20;		

		string text;
		switch (item.first)
		{
		case ItemData::Weapon:
			text = "무기";
			break;
		case ItemData::Armor:
			text = "방어구";
			break;
		}
		TextOutA(hdc, pos.x, pos.y, text.c_str(), text.length());

		pos += Vector2::Down() * 20;
				
		if (item.second)
			text = "장착 아이템 : " + item.second->GetItemData().name;
		else
			text = "장착 아이템 : 없음";

		TextOutA(hdc, pos.x, pos.y, text.c_str(), text.length());
	}
}

void EquipPanel::OnEquipItem(void* equipItem)
{
	InventoryItem* item = (InventoryItem*)equipItem;

	if (equipItems[item->GetItemData().type])
	{
		equipItems[item->GetItemData().type]->Unequip();
	}

	equipItems[item->GetItemData().type] = item;
}

void EquipPanel::OnUnequipItem(void* equipItem)
{
	InventoryItem* item = (InventoryItem*)equipItem;

	equipItems[item->GetItemData().type] = nullptr;
}
