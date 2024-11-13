#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Transform.h"
#include "Layer.h"

template<typename T>
static T* Instantiate(eLayerType type)
{
	T* gameObject = new T();
	Scene* activeScene = SceneManager::GetActiveScene();
	Layer* layer = activeScene->GetLayer(type);
	layer->AddGameObject(gameObject);
	return gameObject;
}

template<typename T>
static T* Instantiate(eLayerType type, Vector2 pos)
{
	T* gameObject = new T();
	Scene* activeScene = SceneManager::GetActiveScene();
	Layer* layer = activeScene->GetLayer(type);
	layer->AddGameObject(gameObject);

	Transform* tr = gameObject->GetComponent<Transform>();
	tr->SetPos(pos);

	return gameObject;
}