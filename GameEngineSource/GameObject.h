#pragma once
#include "CommonInclude.h"
#include "Component.h"

void Destroy(GameObject* gameObject);

class GameObject
{
	friend void Destroy(GameObject* gmaeObject);

public:

	enum class eState
	{
		Active,
		Paused,
		Dead,
		End,
	};
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
	
	eState GetState() { return mState; }
	void SetState(bool power) 
	{
		if (power) mState = eState::Active;
		else mState = eState::Paused;
	}

	bool IsActive() { return eState::Active == mState; }
	bool IsDead() { return mState == eState::Dead; }
private:
	void initializeTransform();
	void death() { mState = eState::Dead; }
private:
	eState mState;
	std::vector<Component*> mComponents;
};

