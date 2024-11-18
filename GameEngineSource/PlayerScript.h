#pragma once
#include "Script.h"
class PlayerScript : public Script
{
public:
	enum class eState
	{
		Idle,
		Walk,
		Sleep,
		GiveWater,
		Attack,
	};
	PlayerScript();
	virtual ~PlayerScript();

	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hdc) override;
	
	void AttackEffect();


	void OnCollisionEnter(class Collider* other) override;
	void OnCollisionStay(class Collider* other) override;
	void OnCollisionExit(class Collider* other) override;


private:
	void idle();
	void move();
	void giveWater();
private:
	eState mState;
	class Animator* mAnimator;
};

