#pragma once

class Circle : public GameObject
{
public:
	Circle(int radius);
	~Circle();

	void Render(HDC hdc);

	bool IsCollisionPoint(POINT point);
	bool IsCollisionCircle(Circle* circle);

protected:
	int radius;
};