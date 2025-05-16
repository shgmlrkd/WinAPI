#include "Framework.h"

InventoryPanel::InventoryPanel()
	: Panel(Vector2(200, CENTER_Y), Vector2(400, 500), RGB(0, 0, 255))
{
	//EventManager::Get()->AddEvent("AddItem", bind(&InventoryPanel::AddItem, this, placeholders::_1));
}

InventoryPanel::~InventoryPanel()
{	
}

void InventoryPanel::Update()
{
	if (!isActive)
		return;

	if (Input::Get()->IsKeyDown(VK_F1))
	{
		//AddItem(DataManager::Get()->GetItem(1001));
	}

	Panel::Update();

	int count = 0;
	for (InventoryItem* item : InventoryPlayer::Get()->items)
	{
		Vector2 size = item->GetSize();
		Vector2 startPos(Left() + size.x, Top() + size.y);
		Vector2 coord(count % COL_COUNT, count / COL_COUNT);

		item->SetCenter(startPos + size * coord + SPACE * coord);
		item->Update();
		count++;
	}
}

void InventoryPanel::Render(HDC hdc)
{
	if (!isActive)
		return;

	Panel::Render(hdc);

	for (InventoryItem* item : InventoryPlayer::Get()->items)
	{
		item->Render(hdc);
	}
}
