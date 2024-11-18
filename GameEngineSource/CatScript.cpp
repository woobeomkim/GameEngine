#include "CatScript.h"
#include "Component.h"
#include "GameObject.h"
#include "Animator.h"
#include "Time.h"
#include "Transform.h"
#include "Object.h"
#include "Input.h"

CatScript::CatScript()
	:mState(eState::SitDown)
	, mAnimator(nullptr)
	, mDir(eDirection::End)
	, mTime(0.0f)
	, mDeathTime(0.0f)
	, mDest(Vector2::Zero)
	, mRadian(0.0f)
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
	mDeathTime += Time::DeltaTime();
	if (mDeathTime > 6.0)
		Destroy(GetOwner());

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

	Transform* tr = GetOwner()->GetComponent<Transform>();
	Vector2 pos = tr->GetPosition();

	mDest = Input::GetMousePos();
	Transform* plTr = mPlayer->GetComponent<Transform>();
	Vector2 dest = mDest - plTr->GetPosition();
	pos += dest.normalize() * (100.0f * Time::DeltaTime());

	// 삼각함수를 통한 이동

	/*mRadian += 5.0f * Time::DeltaTime();
	pos += Vector2(1.0f, 2.0f * cosf(mRadian)) * (100.0f * Time::DeltaTime());*/

	// 마우스 위치 방향으로 회전후 마우스 위치 이동 ( 벡터의 뻴셈 활용)
	//Transform* plTr = mPlayer->GetComponent<Transform>();
	//Vector2 dest = mDest - plTr->GetPosition();
	//dest.normalize();
	//
	//float rotDegree = Vector2::Dot(dest, Vector2::Right);
	//rotDegree = acosf(rotDegree);
	//
	//rotDegree = ConvertDegree(rotDegree);
	//
	//dest = Vector2::Rotate(dest, rotDegree);
	//pos += dest * (100.0f * Time::DeltaTime());

	tr->SetPos(pos);
	/*if (mTime > 3.0f)
	{
		mState = CatScript::eState::Walk;
		int direction = rand() % (UINT)eDirection::End;
		mDir = (eDirection)direction;
		PlayWalkAnimationByDirection(mDir);
		mTime = 0.0f;
	}*/
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
