#pragma once
#include "Component.h"
class SpriteRenderer : public Component
{
public:
	SpriteRenderer();
	virtual ~SpriteRenderer();

	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hdc) override;

	void SetTexture(class Texture* texture) { mTexture = texture; }
	class Texture* GetTexture() { return mTexture; }
	void SetSize(Vector2 size) { mSize = size; }
	Vector2 GetSize() { return mSize; }
private:
	class Texture* mTexture;
	Vector2 mSize;
};

