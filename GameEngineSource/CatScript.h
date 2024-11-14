#pragma once
#include "Script.h"
class CatScript : public Script
{
public:
	enum class eState
	{
		SitDown,
		Walk,
		Sleep,
		LayDown,
		Attack,
	};
	enum class eDirection
	{
		Left,
		Right,
		Down,
		Up,
		End,
	};
	CatScript();
	virtual ~CatScript();

	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hdc) override;

private:
	void sitDown();
	void move();
	void layDown();

	void PlayWalkAnimationByDirection(eDirection dir);
	void translate(class Transform* tr);
private:
	eState mState;
	class Animator* mAnimator;
	eDirection mDir;
	float mTime;
};

