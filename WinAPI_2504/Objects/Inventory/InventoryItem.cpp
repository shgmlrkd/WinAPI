#include "Framework.h"

InventoryItem::InventoryItem(Vector2 center, ItemData itemData)
	: Button(center, Vector2(100, 100)), itemData(itemData)
{
	SetBrush(RGB(255, 0, 0), RGB(200, 0, 0), RGB(150, 0, 0));

	selectedPen = CreatePen(PS_SOLID, 10, RGB(0, 255, 0));	

	EventManager::Get()->AddEvent("ClickInvenItem",
		bind(&InventoryItem::OnSelectedItem, this, placeholders::_1));

	SetEvent(bind(&InventoryItem::OnClickItem, this));

	equipButton = new Button(Vector2::Zero(), Vector2(30, 30));
	equipButton->SetText(L"E");
	equipButton->SetBrush(RGB(100, 100, 100), RGB(80, 80, 80), RGB(50, 50, 50));
	equipButton->SetEvent(bind(&InventoryItem::OnClickEquip, this));

	unequipButton = new Button(Vector2::Zero(), Vector2(30, 30));
	unequipButton->SetText(L"X");
	unequipButton->SetBrush(RGB(100, 100, 100), RGB(80, 80, 80), RGB(50, 50, 50));
	unequipButton->SetEvent(bind(&InventoryItem::OnClickUnequip, this));
}

InventoryItem::~InventoryItem()
{
	DeleteObject(selectedPen);

	delete equipButton;
}

void InventoryItem::Update()
{
	Button::Update();

	if (isSelected && itemData.type != ItemData::Potion)
	{
		if (isEquiped)
		{
			unequipButton->SetCenter(Right(), Bottom());
			unequipButton->Update();
		}
		else
		{
			equipButton->SetCenter(Left(), Bottom());
			equipButton->Update();
		}
	}
}

void InventoryItem::Render(HDC hdc)
{
	if (isSelected)
		defaultPen = (HPEN)SelectObject(hdc, selectedPen);

	Button::Render(hdc);

	if (isSelected)
		SelectObject(hdc, defaultPen);

	string text = "Name : " + itemData.name;
	TextOutA(hdc, Left() + 10, Top() + 10, text.c_str(), text.length());	
	text = "Value : " + to_string(itemData.value);
	TextOutA(hdc, Left() + 10, Top() + 30, text.c_str(), text.length());

	switch (itemData.type)
	{
	case ItemData::Weapon:
		text = "Type : 무기";
		break;
	case ItemData::Armor:
		text = "Type : 방어구";
		break;
	case ItemData::Potion:
		text = "Type : 물약";
		break;	
	}
	
	TextOutA(hdc, Left() + 10, Top() + 50, text.c_str(), text.length());
	text = "Count : " + to_string(count);
	TextOutA(hdc, Left() + 10, Top() + 70, text.c_str(), text.length());	

	if (isSelected && itemData.type != ItemData::Potion)
	{
		if (isEquiped)
		{			
			unequipButton->Render(hdc);
		}
		else
		{
			equipButton->Render(hdc);
		}
	}
}

void InventoryItem::OnSelectedItem(void* item)
{
	isSelected = (item == this);	
}

void InventoryItem::OnClickItem()
{
	EventManager::Get()->ExcuteEvent("ClickInvenItem", this);
}

void InventoryItem::OnClickEquip()
{
	isEquiped = true;
	EventManager::Get()->ExcuteEvent("Equip", this);
}

void InventoryItem::OnClickUnequip()
{
	isEquiped = false;
	EventManager::Get()->ExcuteEvent("Unequip", this);
}
