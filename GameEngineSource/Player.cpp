#include "Player.h"
#include "Input.h"
#include "Time.h"
#include "Transform.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::Init()
{
	GameObject::Init();
}

void Player::Update()
{
	GameObject::Update();
}

void Player::LateUpdate()
{
	GameObject::LateUpdate();
}

void Player::Render(HDC hdc)
{
	GameObject::Render(hdc);
}
