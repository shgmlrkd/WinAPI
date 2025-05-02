#pragma once

class Circle
{
public:
	Circle(int radius);
	~Circle();

	void Render(HDC hdc);

	bool IsCollisionPoint(POINT point);
	bool IsCollisionCircle(Circle* circle);
	

	void SetCenter(int x, int y) { center = { x, y }; }
	void SetCenter(POINT center) { this->center = center; }
	POINT GetCenter() { return center; }

	void SetActive(bool isActive) { this->isActive = isActive; }
	bool IsActive() { return isActive; }

protected:
	bool isActive = true;

	POINT center = {};
	int radius;
};