#pragma once
#include "Component.h"

class Collider : public Component
{
public:
	Collider(eColliderType type);
	virtual ~Collider();

	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hdc) override;

	virtual void OnCollisionEnter(Collider* other);
	virtual void OnCollisionStay(Collider* other);
	virtual void OnCollisionExit(Collider* other);


	void SetOffset(Vector2 offset) { mOffset = offset; }
	Vector2 GetOffset() { return mOffset; }
	Vector2 GetSize() { return mSize; }
	UINT32 GetID() { return mID; }
	void SetSize(Vector2 size) { mSize = size; }
	eColliderType GetColliderType() { return mType; }
private:
	static UINT CollisionID;

	UINT32 mID;
	Vector2 mOffset;
	Vector2 mSize;

	eColliderType mType;
};

