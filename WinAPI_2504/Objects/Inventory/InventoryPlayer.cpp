#include "Framework.h"

InventoryPlayer::InventoryPlayer()
{
	//EventManager::Get()->AddEvent("AddItem", bind(&InventoryPlayer::AddItem, this, placeholders::_1));
	EventManager::Get()->AddEvent("ClickInvenItem", bind(&InventoryPlayer::OnSelectedItem, this, placeholders::_1));
}

InventoryPlayer::~InventoryPlayer()
{
}

void InventoryPlayer::AddItem(void* selectGood)
{
	if (items.size() >= MAX_ITEM_COUNT)
	{
		MessageBox(hWnd, L"Inventory is full", L"Error", MB_OK);
		return;
	}

	Good* good = static_cast<Good*>(selectGood);
	ItemData data = good->GetItemData();

	if (gold < data.price)
	{
		MessageBox(hWnd, L"Not enough gold", L"Error", MB_OK);
		return;
	}

	if (data.type == ItemData::Potion && getItems[data.name] > 0)
	{
		for (InventoryItem* item : items)
		{
			if (item->GetItemData().name == data.name)
			{
				item->AddCount(1);
				break;
			}
		}

		//selectedItem->AddCount(1);
		return;
	}

	Vector2 pos;	
	InventoryItem* newGood = new InventoryItem(pos, data);
	items.push_back(newGood);

	gold -= data.price;

	getItems[data.name]++;
}

void InventoryPlayer::RemoveItem()
{
	if(selectedItem == nullptr)
	{
		MessageBox(hWnd, L"선택한 아이템이 없습니다.", L"Error", MB_OK);
		return;
	}

	ItemData data = selectedItem->GetItemData();

	gold += data.price >> 1;

	getItems[data.name]--;

	if (data.type == ItemData::Potion && selectedItem->GetCount() > 1)
	{
		selectedItem->AddCount(-1);		
		return;
	}

	for (int i = 0; i < items.size(); i++)
	{
		if (selectedItem == items[i])
		{
			items.erase(items.begin() + i);
			selectedItem = nullptr;
			break;
		}
	}

	getItems[selectedItem->GetItemData().name]--;

	//vector<InventoryItem*>::iterator iter = items.begin();
	//
	//for (; iter != items.end(); )
	//{
	//	if ((*iter)->GetItemData().name == selectedItem->GetItemData().name)
	//	{
	//		iter = items.erase(iter);
	//	}
	//	else
	//	{
	//		iter++;
	//	}
	//}
}

void InventoryPlayer::OnSelectedItem(void* item)
{
	selectedItem = (InventoryItem*)item;
}
