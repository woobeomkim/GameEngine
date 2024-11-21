#include "Rigidbody.h"
#include "Time.h"
#include "Transform.h"
#include "GameObject.h"

Rigidbody::Rigidbody()
	:Component(eComponentType::Rigidbody)
	, mMass(1.0f)
	,mFriction(10.0f)
	, mForce(Vector2::Zero)
	, mVelocity(Vector2::Zero)
	, mGravity(Vector2::Zero)
	, mAccelation(Vector2::Zero)
{
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::Init()
{
}

void Rigidbody::Update()
{
	// f(��) = m(����) a(���ӵ�)
	// a = f / m
	mAccelation = mForce / mMass;

	// �ӵ��� ���ӵ��� ���Ѵ�.
	mVelocity += mAccelation * Time::DeltaTime();

	if (!(mVelocity == Vector2::Zero))
	{
		// �ӵ��� �ݴ�������� ������ �ۿ�
		Vector2 friction = -mVelocity;
		friction = friction.normalize() * mFriction * mMass * Time::DeltaTime();

		// ���������� ���� �ӵ� ���ҷ��� ���� �ӵ����� ū ���
		if (mVelocity.length() <= friction.length())
		{
			// ����
			mVelocity = Vector2::Zero;
		}
		else
		{
			mVelocity += friction;
		}
	}

	Transform* tr = GetOwner()->GetComponent<Transform>();
	Vector2 pos = tr->GetPosition();
	pos = pos + mVelocity * Time::DeltaTime();
	tr->SetPos(pos);

	mForce.clear();
}

void Rigidbody::LateUpdate()
{
}

void Rigidbody::Render(HDC hdc)
{
}
