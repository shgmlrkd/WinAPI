#pragma once

class BulletManager
{
private:
	const int BULLET_POOL_SIZE = 50;	

private:
	BulletManager();
	~BulletManager();

public:
	static BulletManager* Get()
	{
		if (instance == nullptr)
			instance = new BulletManager();
		return instance;
		//static BulletManager instance;
		//return &instance;
	}
	static void Delete()
	{
		delete instance;
	}

	void Update();
	void Render(HDC hdc);

	bool IsCollision(Circle* circle);
	

	void Fire(POINT pos);

private:
	static BulletManager* instance;
	
	vector<Bullet*> bullets;	
};