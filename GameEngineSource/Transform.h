#pragma once
#include "Component.h"
class Transform : public Component
{

public:
	Transform();
	virtual ~Transform();

	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hdc) override;

	void SetPos(Vector2 pos) { mPos = pos; }
	Vector2 GetPosition() { return mPos; }
private:
	Vector2 mPos;
};

