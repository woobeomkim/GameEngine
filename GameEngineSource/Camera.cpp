#include "Camera.h"
#include "Application.h"
#include "Transform.h"
#include "GameObject.h"

extern Application app;

Camera::Camera() 
	: Component(eComponentType::Camera)
	 ,mTarget(nullptr)
	 ,mDistance(Vector2::Zero)
	, mLookPosition(Vector2::Zero)
	, mResolution(Vector2::Zero)
{
}

Camera::~Camera()
{
}

void Camera::Init()
{
	mResolution.x = app.GetWidth();
	mResolution.y = app.GetHeight();
}

void Camera::Update()
{
	if (mTarget)
	{
		Transform* tr = mTarget->GetComponent<Transform>();
		mLookPosition = tr->GetPosition();
	}
	else
	{
		Transform* cameraTr = GetOwner()->GetComponent<Transform>();
		mLookPosition = cameraTr->GetPosition();
	}
	mDistance = mLookPosition - (mResolution / 2.0f);
}

void Camera::LateUpdate()
{
}

void Camera::Render(HDC hdc)
{
}
