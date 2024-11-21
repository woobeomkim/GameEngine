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
	float mMass; // ����
	float mFriction; // ������

	Vector2 mForce;
	Vector2 mAccelation;
	Vector2 mVelocity; // �ӵ�
	Vector2 mGravity;
};

