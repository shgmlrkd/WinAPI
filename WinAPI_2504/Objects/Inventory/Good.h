#pragma once

class Good : public Button
{
public:
	Good(Vector2 center, ItemData itemData);
	~Good();

	void Render(HDC hdc);

	ItemData GetItemData() { return itemData; }

private:
	ItemData itemData;
};