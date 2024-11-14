#include "CatScript.h"
#include "Component.h"
#include "GameObject.h"
#include "Animator.h"
#include "Time.h"
#include "Transform.h"

CatScript::CatScript()
	:mState(eState::SitDown)
	, mAnimator(nullptr)
	, mDir(eDirection::End)
	, mTime(0.0f)
{

}
CatScript::~CatScript()
{
}

void CatScript::Init()
{
}

void CatScript::Update()
{
	if (mAnimator == nullptr)
		mAnimator = GetOwner()->GetComponent<Animator>();

	switch (mState)
	{
	case CatScript::eState::SitDown:
		sitDown();
		break;
	case CatScript::eState::Walk:
		move();
		break;
	case CatScript::eState::Sleep:
		break;
	case CatScript::eState::LayDown:
		layDown();
		break;
	case CatScript::eState::Attack:
		break;
	default:
		break;
	}
}

void CatScript::LateUpdate()
{
}

void CatScript::Render(HDC hdc)
{
}

void CatScript::sitDown()
{
	mTime += Time::DeltaTime();
	if (mTime > 3.0f)
	{
		mState = CatScript::eState::Walk;
		int direction = rand() % (UINT)eDirection::End;
		mDir = (eDirection)direction;
		PlayWalkAnimationByDirection(mDir);
		mTime = 0.0f;
	}
}

void CatScript::move()
{
	mTime += Time::DeltaTime();
	if (mTime > 2.0f)
	{
		int isLayDown = rand() % 2;
		if (isLayDown)
		{
			mState = eState::LayDown;
			mAnimator->PlayAnimation(L"LayDown", false);
		}
		else
		{
			mState = eState::SitDown;
			mAnimator->PlayAnimation(L"SitDown", false);
		}
	}

	Transform* tr = GetOwner()->GetComponent<Transform>();
	translate(tr);
}

void CatScript::layDown()
{
}

void CatScript::PlayWalkAnimationByDirection(eDirection dir)
{
	switch (dir)
	{
	case CatScript::eDirection::Left:
		mAnimator->PlayAnimation(L"LeftWalk", true);
		break;
	case CatScript::eDirection::Right:
		mAnimator->PlayAnimation(L"RightWalk", true);
		break;
	case CatScript::eDirection::Down:
		mAnimator->PlayAnimation(L"DownWalk", true);
		break;
	case CatScript::eDirection::Up:
		mAnimator->PlayAnimation(L"UpWalk", true);
		break;
	case CatScript::eDirection::End:
		assert(false);
		break;
	default:
		break;
	}
}

void CatScript::translate(Transform* tr)
{
	Vector2 pos = tr->GetPosition();
	switch (mDir)
	{
	case CatScript::eDirection::Left:
		pos.x -= 100.0f * Time::DeltaTime();
		break;
	case CatScript::eDirection::Right:
		pos.x += 100.0f * Time::DeltaTime();
		break;
	case CatScript::eDirection::Down:
		pos.y += 100.0f * Time::DeltaTime();
		break;
	case CatScript::eDirection::Up:
		pos.y -= 100.0f * Time::DeltaTime();
		break;
	default:
		break;
	}
	tr->SetPos(pos);
}
