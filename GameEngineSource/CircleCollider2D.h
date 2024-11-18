#pragma once
#include "Collider.h"
class CircleCollider2D : public Collider
{
public:
	CircleCollider2D();
	virtual ~CircleCollider2D();

	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hdc) override;

private:
	float mRadius;
};

