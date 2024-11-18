#include "GameObject.h"
#include "Input.h"
#include "Time.h"
#include "Transform.h"

GameObject::GameObject()
	: mState(eState::Active)
	, mLayerType(eLayerType::None)
{
	mComponents.resize((UINT)eComponentType::End);
	initializeTransform();
}

GameObject::~GameObject()
{
	for (Component* comp : mComponents)
	{
		if (comp)
		{
			delete comp;
			comp = nullptr;
		}
	}
}

void GameObject::Init()
{
	for (Component* comp : mComponents)
	{
		if (comp)
		{
			if (comp == nullptr)
				continue;
			comp->Init();
		}
	}
}
void GameObject::Update()
{
	for (Component* comp : mComponents)
	{
		if (comp)
		{
			if (comp == nullptr)
				continue;
			comp->Update();
		}
	}
}

void GameObject::LateUpdate()
{
	for (Component* comp : mComponents)
	{
		if (comp)
		{
			if (comp == nullptr)
				continue;
			comp->LateUpdate();
		}
	}
}

void GameObject::Render(HDC hdc)
{
	for (Component* comp : mComponents)
	{
		if (comp)
		{
			if (comp == nullptr)
				continue;
			comp->Render(hdc);
		}
	}
}

void GameObject::initializeTransform()
{
	AddComponent<Transform>();
}

void Destroy(GameObject* gameObject)
{
	if (gameObject != nullptr)
		gameObject->death();
}
