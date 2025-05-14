#pragma once

class Rect : public GameObject
{
public:
	Rect();
	Rect(Vector2 center, Vector2 size);
	~Rect();

	void Render(HDC hdc);

	float Left() { return center.x - size.x * 0.5f; }
	float Right() { return center.x + size.x * 0.5f; }
	float Top() { return center.y - size.y * 0.5f; }
	float Bottom() { return center.y + size.y * 0.5f; }

	bool IsCollisionPoint(Vector2 point);

protected:	
	Vector2 size;
};