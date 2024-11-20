#include "Scene.h"
#include "GameObject.h"
#include "Layer.h"
#include "CollisionManager.h"

Scene::Scene()
	:mLayers{}
{
	CreateLayers();
}

Scene::~Scene()
{
	for (Layer* layer : mLayers)
	{
		delete layer;
		layer = nullptr;
	}
}

void Scene::Init()
{
	for (Layer* layer : mLayers)
	{
		if (layer == nullptr)
			continue;
		layer->Init();	
	}
}

void Scene::Update()
{
	for (Layer* layer : mLayers)
	{	
		if (layer == nullptr)
			continue;
		layer->Update();
	}
}
void Scene::LateUpdate()
{

	for (Layer* layer : mLayers)
	{
		if (layer == nullptr)
			continue;
		layer->LateUpdate();
	}
}

void Scene::Render(HDC hdc)
{

	for (Layer* layer : mLayers)
	{
		if (layer == nullptr)
			continue;
		layer->Render(hdc);
	}
}

void Scene::Destroy()
{
	for (Layer* layer : mLayers)
	{
		if (layer == nullptr)
			continue;
		layer->Destroy();
	}
}

void Scene::OnEnter()
{
}

void Scene::OnExit()
{
	CollisionManager::Clear();
}

void Scene::AddGameObject(GameObject* gameObject, const eLayerType type)
{
	mLayers[(UINT)type]->AddGameObject(gameObject);
}

void Scene::CreateLayers()
{
	mLayers.resize((UINT)eLayerType::Max);
	for (size_t i = 0; i < (UINT)eLayerType::Max; i++)
	{
		mLayers[i] = new Layer();
	}
}

void Scene::EraseGameObject(GameObject* gameObj)
{
	eLayerType layerType = gameObj->GetLayerType();
	mLayers[(UINT)layerType]->EraseGameObject(gameObj);
}
