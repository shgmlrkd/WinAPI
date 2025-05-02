#pragma once

class Circle
{
public:
	Circle(int radius);
	~Circle();

	void Render(HDC hdc);

	void SetCenter(int x, int y) { center = { x, y }; }
	void SetCenter(POINT center) { this->center = center; }
	POINT GetCenter() { return center; }

protected:
	POINT center = {};
	int radius;
};