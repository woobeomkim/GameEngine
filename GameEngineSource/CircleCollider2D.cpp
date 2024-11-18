#include "CircleCollider2D.h"
#include "Transform.h"
#include "Component.h"
#include "GameObject.h"
#include "Camera.h"
#include "MainCamera.h"

CircleCollider2D::CircleCollider2D()
	:Collider(eColliderType::Circle2D)
	,mRadius(0.0f)
{
}

CircleCollider2D::~CircleCollider2D()
{
}

void CircleCollider2D::Init()
{
}

void CircleCollider2D::Update()
{
}

void CircleCollider2D::LateUpdate()
{
}

void CircleCollider2D::Render(HDC hdc)
{
	Transform* tr = GetOwner()->GetComponent<Transform>();
	Vector2 pos = tr->GetPosition();

	if (mainCamera)
		pos = mainCamera->CalculatePosition(pos);

	Vector2 offset = GetOffset();

	HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);

	HPEN greenPen = (HPEN)CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
	HPEN oldPen = (HPEN)SelectObject(hdc, greenPen);

	Vector2 rightBottom;
	rightBottom.x = pos.x + offset.x + 100 * GetSize().x;
	rightBottom.y = pos.y + offset.y + 100 * GetSize().y;

	Ellipse(hdc
		, pos.x + offset.x
		, pos.y + offset.y
		, rightBottom.x
		, rightBottom.y);

	SelectObject(hdc, oldBrush);
	SelectObject(hdc, oldPen);
	DeleteObject(greenPen);
}
