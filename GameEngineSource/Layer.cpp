#include "Layer.h"

Layer::Layer()
{
}

Layer::~Layer()
{
	for (GameObject* obj : mGameObjects)
	{
		if (obj == nullptr)
			continue;
		delete obj;
		obj = nullptr;
	}
}

void Layer::Init()
{
	for (GameObject* obj : mGameObjects)
	{
		if (obj == nullptr)
			continue;
		obj->Init();
	}
}
void Layer::Update()
{
	for (GameObject* obj : mGameObjects)
	{
		if (obj == nullptr)
			continue;
		if (!obj->IsActive())
			continue;

		obj->Update();
	}
}

void Layer::LateUpdate()
{
	for (GameObject* obj : mGameObjects)
	{
		if (obj == nullptr)
			continue;
		if (!obj->IsActive())
			continue;

		obj->LateUpdate();
	}
}
void Layer::Render(HDC hdc)
{
	for (GameObject* obj : mGameObjects)
	{
		if (obj == nullptr)
			continue;
		if (!obj->IsActive())
			continue;
		obj->Render(hdc);
	}
}
void Layer::Destroy()
{
	std::vector<GameObject*> deleteObjects = {};
	findDeadGameObjects(deleteObjects);
	eraseDeadGameObjects();
	deleteGameObjects(deleteObjects);
}
void Layer::AddGameObject(GameObject* gameObject)
{
	if (gameObject == nullptr)
		return;
	mGameObjects.push_back(gameObject);
}

void Layer::EraseGameObject(GameObject* eraseGameObj)
{
	std::erase_if(mGameObjects, [=](GameObject* gameObj)
		{
			return gameObj == eraseGameObj;
		});
}

void Layer::findDeadGameObjects(OUT std::vector<GameObject*>& gameObjs)
{
	for (GameObject* gameObj : mGameObjects)
	{
		GameObject::eState active = gameObj->GetState();
		
		if(active == GameObject::eState::Dead)
			gameObjs.push_back(gameObj);
	}
}

void Layer::deleteGameObjects(std::vector<GameObject*>& gameObjs)
{
	for (GameObject* obj : gameObjs)
	{
		delete obj;
		obj = nullptr;
	}
}

void Layer::eraseDeadGameObjects()
{
	std::erase_if(mGameObjects,
		[](GameObject* gameObj)
		{
			return (gameObj)->IsDead();
		});
}
