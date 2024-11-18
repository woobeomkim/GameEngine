#pragma once
#include "CommonInclude.h"

class Scene;

class SceneManager
{
public:
	template<typename T>
	static Scene* CreateScene(const std::wstring& name)
	{
		T* scene = new T();
		mActiveScene = scene;
		scene->SetName(name);
		scene->Init();

		mScene.insert(std::make_pair(name, scene));

		return scene;
	}

	static Scene* LoadScene(const std::wstring& name);

	static void Init();
	static void Update();
	static void LateUpdate();
	static void Render(HDC hdc);
	static void Destroy();
	static void Release();

	static Scene* GetActiveScene() { return mActiveScene; }
	static Scene* GetDontDestroyScene() { return mDontDestroyOnLoad; }
private:
	static std::map<std::wstring, Scene*> mScene;
	static Scene* mActiveScene;
	static Scene* mDontDestroyOnLoad;
};

