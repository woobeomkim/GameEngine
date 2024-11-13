#pragma once
#include "Component.h"
class Animator : public Component
{
public:
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
private:
	std::map<std::wstring, class Animation*> mAnimations;
	class Animation* mActiveAnimation;
	bool mbLoop;
};

