#pragma once

class Player : public Circle
{
private:
	const int SPEED = 10;

public:
	Player();
	~Player();

	void Update();		
};