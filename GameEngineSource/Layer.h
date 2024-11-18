#pragma once
#include "Entity.h"
#include "CommonInclude.h"
#include "GameObject.h"

class Layer : public Entity
{
public:
	Layer();
	~Layer();

	virtual void Init();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render(HDC hdc);
	virtual void Destroy();

	void AddGameObject(GameObject* gameObject);
	const std::vector<GameObject*>& GetGameObjects() { return mGameObjects; }
private:
	void findDeadGameObjects(OUT std::vector<GameObject*>& gameObjs);
	void deleteGameObjects(std::vector<GameObject*>& gameObjs);
	void eraseGameObjects();

private:
	std::vector<GameObject*> mGameObjects;
};

