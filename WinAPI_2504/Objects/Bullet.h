#pragma once

class Bullet : public Circle
{
private:
	const float SPEED = 500;

public:
	Bullet();
	~Bullet();

	void Update();

	void Fire(Vector2 pos, Vector2 direction = Vector2::Up())
	{
		this->direction = direction;
		isActive = true;
		center = pos;
	}

private:
	Vector2 direction = Vector2::Up();
};