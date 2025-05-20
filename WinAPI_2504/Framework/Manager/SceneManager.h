#pragma once

class SceneManager : public Singleton<SceneManager>
{
public:
	SceneManager();
	~SceneManager();

	void Update();
<<<<<<< HEAD
	void Render(HDC hdc);
=======
	void Render();
>>>>>>> upstream/main

	void AddScene(string key, Scene* scene);
	void ChangeScene(string key);

private:
	Scene* currentScene;
	
	unordered_map<string, Scene*> scenes;
};