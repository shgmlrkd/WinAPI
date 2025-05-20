#pragma once

//Interface
class Scene
{
public:
	//Scene() {}
	Scene() = default;	
	~Scene() = default;
		
	virtual void Update() = 0;
<<<<<<< HEAD
	virtual void Render(HDC hdc) = 0;
=======
	virtual void Render() = 0;
>>>>>>> upstream/main

	virtual void Start() {}
	virtual void End() {}
};