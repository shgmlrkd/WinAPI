#pragma once

class GameObject
{
public:
	GameObject() = default;
	GameObject(Vector2 center) : center(center) {}
	~GameObject() = default;
	
	void SetCenter(float x, float y) { center = { x, y }; }
	void SetCenter(Vector2 center) { this->center = center; }
	Vector2 GetCenter() { return center; }

	void SetActive(bool isActive) { this->isActive = isActive; }
	bool IsActive() { return isActive; }	

protected:
	bool isActive = true;

	Vector2 center = {};	
};