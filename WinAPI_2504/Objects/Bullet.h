#pragma once

class Bullet : public Circle
{
private:
	const int SPEED = 20;

public:
	Bullet();
	~Bullet();

	void Update();

	void Fire(POINT pos)
	{
		isActive = true;
		center = pos;
	}
};