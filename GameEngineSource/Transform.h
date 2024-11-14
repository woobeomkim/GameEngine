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
	void SetScale(Vector2 scale) { mScale = scale; }
	Vector2 GetScale() { return mScale; }
	void SetRotation(float rotation) { mRotation = rotation; }
	float GetRotation() { return mRotation; }
private:
	Vector2 mPos;
	Vector2 mScale;
	float mRotation;
};

