#pragma once

class BulletManager : public Singleton<BulletManager>
{
	friend class Singleton;

private:
	const int BULLET_POOL_SIZE = 200;	

private:
	BulletManager();
	~BulletManager();

public:
	void Update();
	void Render(HDC hdc);

	bool IsCollision(Circle* circle);	

	void Fire(Vector2 pos, Vector2 direction = Vector2::Up());

private:
	vector<Bullet*> bullets;	
};