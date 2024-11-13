#pragma once
#include "Entity.h"

class GameObject;

class Component : public Entity
{
public:
	Component(eComponentType type);
	virtual ~Component();

	virtual void Init();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render(HDC hdc);

	void SetOwner(GameObject* owner) { mOwner = owner; }
	GameObject* GetOwner() { return mOwner; }
	eComponentType GetComponentType() { return mType; }

private:
	eComponentType mType;
	GameObject* mOwner;

};

