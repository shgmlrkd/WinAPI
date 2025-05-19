#include "Framework.h"

Rect::Rect()
{
}

Rect::Rect(Vector2 center, Vector2 size)
	: GameObject(center), size(size)
{
}

Rect::~Rect()
{
}

void Rect::Render(HDC hdc)
{
	if (!isActive)
		return;

	Rectangle(hdc,
		Left(), Top(),//LeftTop
		Right(), Bottom()//RightBottom
	);
}

bool Rect::IsCollisionPoint(Vector2 point)
{
	if (point.x >= Left() && point.x <= Right())
	{
		if (point.y >= Top() && point.y <= Bottom())
		{
			return true;
		}
	}

    return false;
}
