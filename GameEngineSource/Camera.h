#pragma once
#include "Component.h"
class Camera : public Component
{
public:
	Vector2 CalculatePosition(Vector2 pos) { return pos - mDistance; }

	Camera();
	virtual ~Camera();

	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hdc) override;

	void SetTarget(class GameObject* target) { mTarget = target; }

private:
	class GameObject* mTarget;
	Vector2 mDistance;
	Vector2 mResolution;
	Vector2 mLookPosition;
};

