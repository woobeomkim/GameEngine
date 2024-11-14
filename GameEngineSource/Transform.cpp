#include "Transform.h"
#include "Input.h"
#include "Time.h"


Transform::Transform()
	:Component(eComponentType::Transform)
	, mScale(Vector2::One)
	, mRotation(0.0f)
{
}

Transform::~Transform()
{
}

void Transform::Init()
{
}

void Transform::Update()
{
}

void Transform::LateUpdate()
{
}

void Transform::Render(HDC hdc)
{
}
