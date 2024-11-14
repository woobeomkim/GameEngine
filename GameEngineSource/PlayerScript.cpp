#include "PlayerScript.h"
#include "Transform.h"
#include "Input.h"
#include "Time.h"
#include "GameObject.h"
#include "Animator.h"
#include "Cat.h"
#include "CatScript.h"
#include "Resources.h"
#include "Object.h"
#include "Texture.h"

PlayerScript::PlayerScript()
	:mState(eState::Idle)
	,mAnimator(nullptr)
{
}

PlayerScript::~PlayerScript()
{
}

void PlayerScript::Init()
{
}

void PlayerScript::Update()
{
	if (mAnimator == nullptr)
		mAnimator = GetOwner()->GetComponent<Animator>();

	switch (mState)
	{
	case PlayerScript::eState::Idle:
		idle();
		break;
	case PlayerScript::eState::Walk:
		move();
		break;
	case PlayerScript::eState::Sleep:
		break;
	case PlayerScript::eState::GiveWater:
		giveWater();
		break;
	case PlayerScript::eState::Attack:
		break;
	default:
		break;
	}
}

void PlayerScript::LateUpdate()
{
}

void PlayerScript::Render(HDC hdc)
{
}

void PlayerScript::AttackEffect()
{
	Cat* cat = Instantiate<Cat>(eLayerType::Animal);
	cat->AddComponent<CatScript>();

	Texture* catTexture = Resources::Find<Texture>(L"Cat");
	Animator* catAnimator = cat->AddComponent<Animator>();

	catAnimator->CreateAnimation(L"DownWalk", catTexture, Vector2(0, 0), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.5f);
	catAnimator->CreateAnimation(L"RightWalk", catTexture, Vector2(0, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.5f);
	catAnimator->CreateAnimation(L"UpWalk", catTexture, Vector2(0, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.5f);
	catAnimator->CreateAnimation(L"LeftWalk", catTexture, Vector2(0, 96.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.5f);
	catAnimator->CreateAnimation(L"SitDown", catTexture, Vector2(0, 128.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.5f);
	catAnimator->CreateAnimation(L"Grooming", catTexture, Vector2(0, 160.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.5f);
	catAnimator->CreateAnimation(L"LayDown", catTexture, Vector2(0, 192.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.5f);

	catAnimator->PlayAnimation(L"Idle", false);
	Transform* tr = cat->GetComponent<Transform>();
	tr->SetPos(Vector2(200.0f, 200.0f));
	tr->SetScale(Vector2(2.0f, 2.0f));
}


void PlayerScript::idle()
{
	if (Input::GetKey(eKeyCode::LButton))
	{
		mState = eState::GiveWater;
		mAnimator->PlayAnimation(L"FrontGiveWater", false);
		Vector2 mousePos = Input::GetMousePos();
	}
}

void PlayerScript::move()
{
	Transform* tr = GetOwner()->GetComponent<Transform>();
	Vector2 pos = tr->GetPosition();

	if (Input::GetKey(eKeyCode::Right))
	{
		pos.x += 100.0f * Time::DeltaTime();
	}
	if (Input::GetKey(eKeyCode::Left))
	{
		pos.x -= 100.0f * Time::DeltaTime();
	}
	if (Input::GetKey(eKeyCode::Up))
	{
		pos.y -= 100.0f * Time::DeltaTime();
	}
	if (Input::GetKey(eKeyCode::Down))
	{
		pos.y += 100.0f * Time::DeltaTime();
	}
	tr->SetPos(pos);

	if (Input::GetKeyUp(eKeyCode::Right) || Input::GetKeyUp(eKeyCode::Left) || Input::GetKeyUp(eKeyCode::Up) || Input::GetKeyUp(eKeyCode::Down))
	{
		mState = eState::Idle;
		mAnimator->PlayAnimation(L"SitDown", false);
	}
}

void PlayerScript::giveWater()
{
	if (mAnimator->IsComplete())
	{
		mState = eState::Idle;
		mAnimator->PlayAnimation(L"Idle", false);
	}
}
