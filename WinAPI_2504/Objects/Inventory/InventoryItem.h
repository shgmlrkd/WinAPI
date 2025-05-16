#pragma once

class InventoryItem : public Button
{
public:
	InventoryItem(Vector2 center, ItemData itemData);
	~InventoryItem();

	void Update();
	void Render(HDC hdc);
	
	void Unequip() { isEquiped = false; }

	void OnSelectedItem(void* item);
	void OnClickItem();
	void OnClickEquip();
	void OnClickUnequip();

	ItemData GetItemData() { return itemData; }

	int GetCount() { return count; }
	void AddCount(int value) { count += value; }	

private:
	bool isSelected = false;
	bool isEquiped = false;
	int count = 1;

	ItemData itemData;

	HPEN selectedPen;
	HPEN defaultPen;

	Button* equipButton;
	Button* unequipButton;
};