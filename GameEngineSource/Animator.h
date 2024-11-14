#pragma once
#include "Component.h"
class Animator : public Component
{
public:
	struct Event
	{
		void operator=(std::function<void()> func)
		{
			mEvent = std::move(func);
		}

		void operator()()
		{
			if (mEvent)
				mEvent();
		}
		std::function<void()> mEvent;
	};
	
	struct Events
	{
		Event startEvent;
		Event completeEvent;
		Event endEvent;

	};
	Animator();
	virtual ~Animator();

	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hdc) override;

	void CreateAnimation(const std::wstring& name
		, class Texture* spriteSheet
		, Vector2 leftTop
		, Vector2 size
		, Vector2 offset
		, UINT spriteLength
		, float duration);

	class Animation* FindAnimation(const std::wstring& name);
	void PlayAnimation(const std::wstring& name, bool loop = true);
	Events* FindEvnts(const std::wstring& name);
	std::function<void()>& GetStartEvent(const std::wstring& name);
	std::function<void()>& GetCompleteEvent(const std::wstring& name);
	std::function<void()>& GetEndEvent(const std::wstring& name);


	bool IsComplete();
private:
	std::map<std::wstring, class Animation*> mAnimations;
	class Animation* mActiveAnimation;
	bool mbLoop;

	std::map<std::wstring, Events*> mEvents;
};

