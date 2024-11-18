#pragma once
#include "Collider.h"
class BoxCollider2D : public Collider
{
public:
	BoxCollider2D();
	virtual ~BoxCollider2D();

	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hdc) override;
private:
};

