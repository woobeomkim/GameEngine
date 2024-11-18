#include "BoxCollider2D.h"
#include "Transform.h"
#include "GameObject.h"
#include "Camera.h"
#include "MainCamera.h"

BoxCollider2D::BoxCollider2D()
	:Collider(eColliderType::Rect2D)
{
}

BoxCollider2D::~BoxCollider2D()
{
}

void BoxCollider2D::Init()
{
}

void BoxCollider2D::Update()
{
}

void BoxCollider2D::LateUpdate()
{
}

void BoxCollider2D::Render(HDC hdc)
{
	Transform* tr = GetOwner()->GetComponent<Transform>();
	Vector2 pos = tr->GetPosition();

	if (mainCamera)
		pos = mainCamera->CalculatePosition(pos);

	Vector2 offset = GetOffset();

	HBRUSH transparentBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);

	HPEN greenPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	HPEN oldPen = (HPEN)SelectObject(hdc, greenPen);

	Rectangle(hdc
		, pos.x + offset.x
		, pos.y + offset.y
		, pos.x + offset.x + 100 * GetSize().x
		, pos.y + offset.y + 100 * GetSize().y);
	
	SelectObject(hdc, oldBrush);
	SelectObject(hdc, oldPen);
	DeleteObject(greenPen);
}
