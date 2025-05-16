#pragma once

class InventoryPlayer : public Singleton<InventoryPlayer>
{
	friend class InventoryPanel;

private:
	const int MAX_ITEM_COUNT = 12;

public:
	InventoryPlayer();
	~InventoryPlayer();

	void AddItem(void* selectGood);
	void RemoveItem();

	int GetGold() { return gold; }
	void SetGold(int gold) { this->gold = gold; }

	void OnSelectedItem(void* item);

private:
	int gold = 1000;	

	InventoryItem* selectedItem = nullptr;

	vector<InventoryItem*> items;
	unordered_map<string, int> getItems;	
};