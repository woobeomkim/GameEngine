#pragma once
#include "CommonInclude.h"
#include "Component.h"

class GameObject
{
public:
	GameObject();
	virtual ~GameObject();

	virtual void Init();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render(HDC hdc);

	template<typename T>
	T* AddComponent()
	{
		T* comp = new T();
		comp->Init();
		comp->SetOwner(this);
		
		mComponents[(UINT)comp->GetComponentType()] = comp;

		return comp;
	}

	template<typename T>
	T* GetComponent()
	{
		T* component = nullptr;
		for (Component* comp : mComponents)
		{
			component = dynamic_cast<T*>(comp);
			if (component)
				break;
		}

		return component;
	}

private:
	void initializeTransform();

private:
	std::vector<Component*> mComponents;
};

