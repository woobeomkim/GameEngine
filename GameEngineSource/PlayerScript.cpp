#include "PlayerScript.h"
#include "Transform.h"
#include "Input.h"
#include "Time.h"
#include "GameObject.h"

PlayerScript::PlayerScript()
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
}

void PlayerScript::LateUpdate()
{
}

void PlayerScript::Render(HDC hdc)
{
}
