#include "Layer.h"

Layer::Layer()
{
}

Layer::~Layer()
{
}

void Layer::Init()
{
	for (GameObject* obj : mGameObjects)
	{
		obj->Init();
	}
}
void Layer::Update()
{
	for (GameObject* obj : mGameObjects)
		obj->Update();
}

void Layer::LateUpdate()
{
	for (GameObject* obj : mGameObjects)
		obj->LateUpdate();
}

void Layer::Render(HDC hdc)
{
	for (GameObject* obj : mGameObjects)
		obj->Render(hdc);
}

void Layer::AddGameObject(GameObject* gameObject)
{
	mGameObjects.push_back(gameObject);
}
