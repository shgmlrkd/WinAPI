#include "Framework.h"
#include "Circle.h"

Circle::Circle(int radius) : radius(radius)
{
}

Circle::~Circle()
{
}


void Circle::Render(HDC hdc)
{
	Ellipse(hdc, 
		center.x - radius, center.y - radius,//LeftTop
		center.x + radius, center.y + radius//RightBottom
	);	
}