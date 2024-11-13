#pragma once
#include "Resource.h"
class Animation : public Resource
{
public:
	struct Sprite
	{
		Vector2 leftTop;
		Vector2 size;
		Vector2 offset;
		float duration;

		Sprite() 
			: leftTop(Vector2::Zero)
			, size(Vector2::One)
			, offset(Vector2::Zero)
			, duration(0.0f)
		{}
	};

	Animation();
	virtual ~Animation();

	void Update();
	void Render(HDC hdc);

	HRESULT Load(const std::wstring& path) override;
	
	void CreateAnimation(const std::wstring& name
		, class Texture* spriteSheet
		, Vector2 leftTop
		, Vector2 size
		, Vector2 offset
		, UINT spriteLength
		, float duration);

	void Reset();

	bool IsComplete() { return mbComplete; }
	void SetAnimator(class Animator* animator) { mAnimator = animator; }

private:
	class Animator* mAnimator;
	class Texture* mTexture;
	
	std::vector<Sprite> mAnimationSheet;
	int mIndex;
	float mTime;
	bool mbComplete;
};

