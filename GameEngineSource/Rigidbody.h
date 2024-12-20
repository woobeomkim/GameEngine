#pragma once
#include "Component.h"
class Rigidbody :
    public Component
{
public:
	Rigidbody();
	virtual ~Rigidbody();

	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hdc) override;
	
	void SetMass(float mass) { mMass = mass; }
	void AddForce(Vector2 force) { mForce = force; }
	
private:
	float mMass; // 질량
	float mFriction; // 마찰력

	Vector2 mForce;
	Vector2 mAccelation;
	Vector2 mVelocity; // 속도
	Vector2 mGravity;
};

