#pragma once

class InventoryPanel;

class StorePanel : public Panel
{
public:
	StorePanel();
	~StorePanel();

	void Update() override;
	void Render(HDC hdc) override;

	//void SetInventoryPanel(InventoryPanel* panel) { inventoryPanel = panel; }

private:
	void CreateGoods();

	void BuyItem();
	void SellItem();

	//void������ -> � Ÿ������ �� �� ���
	void OnClickGood(void* good);
	

private:
	vector<Good*> goods;
	Good* selectedGood = nullptr;

	Circle* target;

	Button* buyButton = nullptr;
	Button* sellButton = nullptr;
	//InventoryPanel* inventoryPanel = nullptr;
};