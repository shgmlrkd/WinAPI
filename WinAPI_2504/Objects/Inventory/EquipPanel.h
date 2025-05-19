#pragma once

class EquipPanel : public Panel
{
public:
	EquipPanel();
	~EquipPanel();

	void Update() override;
	void Render(HDC hdc) override;

	void OnEquipItem(void* equipItem);
	void OnUnequipItem(void* equipItem);

private:	
	unordered_map<ItemData::Type, InventoryItem*> equipItems;
};

