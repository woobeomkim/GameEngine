#pragma once
#include "Component.h"

class TilemapRenderer : public Component
{
public:
	TilemapRenderer();
	virtual ~TilemapRenderer();

	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hdc) override;

	void SetTexture(class Texture* texture) { mTexture = texture; }
	class Texture* GetTexture() { return mTexture; }
	void SetSize(Vector2 size) { mSize = size; }
	Vector2 GetSize() { return mSize; }
	Vector2 GetIndex() { return mIndex; }
	void SetIndex(Vector2 index) { mIndex = index; }
public:
	static Vector2 TileSize;
	static Vector2 OriginTileSize;
	static Vector2 SelectedIndex;
private:
	
	class Texture* mTexture;
	Vector2 mSize;
	Vector2 mIndex;
	Vector2 mTileSize;
};

