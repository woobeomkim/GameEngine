#pragma once
#include "Entity.h"

class GameObject;
class Layer;

class Scene : public Entity
{
public:
	Scene();
	virtual ~Scene();

	virtual void Init();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render(HDC hdc);
	virtual void Destroy();

	virtual void OnEnter();
	virtual void OnExit();

	void AddGameObject(GameObject* gameObject,const eLayerType type);
	void CreateLayers();
	Layer* GetLayer(eLayerType type) {	return mLayers[(UINT)type]; }

private:
	std::vector<Layer*> mLayers;
};

