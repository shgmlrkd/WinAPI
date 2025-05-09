#pragma once

class ShootingScene : public Scene
{
public:
	ShootingScene();
	~ShootingScene();

	void Update() override;
	void Render(HDC hdc) override;

	void Start() override;
	void End() override;

private:
	Player* player;	
};