#include "Animator.h"
#include "Animation.h"


Animator::Animator()
	: Component(eComponentType::Animator)
	, mActiveAnimation(nullptr)
	, mAnimations{}
	, mbLoop(false)
	, mEvents{}
{
}

Animator::~Animator()
{
}

void Animator::Init()
{
}

void Animator::Update()
{
	if (mActiveAnimation)
	{
		mActiveAnimation->Update();

		Events* events
			= FindEvnts(mActiveAnimation->GetName());

		if (mActiveAnimation->IsComplete())
		{
			if (events)
				events->completeEvent();

			if(mbLoop)
				mActiveAnimation->Reset();
		}
	}
}

void Animator::LateUpdate()
{
}

void Animator::Render(HDC hdc)
{
	if (mActiveAnimation)
		mActiveAnimation->Render(hdc);
}

void Animator::CreateAnimation(const std::wstring& name, Texture* spriteSheet, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLength, float duration)
{
	Animation* animation = nullptr;
	animation = FindAnimation(name);
	if (animation != nullptr)
		return;

	animation = new Animation();
	animation->SetName(name);
	animation->CreateAnimation(name, spriteSheet, leftTop, size, offset, spriteLength, duration);

	animation->SetAnimator(this);

	Events* events = new Events();
	mEvents.insert(std::make_pair(name, events));

	mAnimations.insert(std::make_pair(name, animation));
}

Animation* Animator::FindAnimation(const std::wstring& name)
{
	auto iter = mAnimations.find(name);

	if (iter == mAnimations.end())
		return nullptr;

	return iter->second;
}

void Animator::PlayAnimation(const std::wstring& name, bool loop)
{
	Animation* animation = FindAnimation(name);
	if (animation == nullptr)
		return;
	
	if (mActiveAnimation)
	{
		Events* currentEvents
			= FindEvnts(mActiveAnimation->GetName());
		if (currentEvents)
			currentEvents->endEvent();
	}

	Events* nextEvents
		= FindEvnts(animation->GetName());
	
	if (nextEvents)
		nextEvents->startEvent();

	mActiveAnimation = animation;
	mActiveAnimation->Reset();
	mbLoop = loop;
}

Animator::Events* Animator::FindEvnts(const std::wstring& name)
{
	auto iter = mEvents.find(name);
	if (iter == mEvents.end())
		return nullptr;
	return iter->second;
}

std::function<void()>& Animator::GetStartEvent(const std::wstring& name)
{
	Events* events = FindEvnts(name);
	return events->startEvent.mEvent;

}

std::function<void()>& Animator::GetCompleteEvent(const std::wstring& name)
{
	Events* events = FindEvnts(name);
	return events->completeEvent.mEvent;
}

std::function<void()>& Animator::GetEndEvent(const std::wstring& name)
{
	Events* events = FindEvnts(name);
	return events->endEvent.mEvent;
}

bool Animator::IsComplete()
{
	 return mActiveAnimation->IsComplete(); 
}
