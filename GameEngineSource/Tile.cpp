#include "Tile.h"
#include "Transform.h"
#include "TilemapRenderer.h"

Tile::Tile()
{
}

Tile::~Tile()
{
}

void Tile::Init()
{
	GameObject::Init();
}

void Tile::Update()
{
	GameObject::Update();
}

void Tile::LateUpdate()
{
	GameObject::LateUpdate();
}

void Tile::Render(HDC hdc)
{
	GameObject::Render(hdc);
}

void Tile::SetIndexPosition(int x, int y)
{
	Transform* tr = GetComponent<Transform>();
	Vector2 pos;
	pos.x = x * TilemapRenderer::TileSize.x;
	pos.y = y * TilemapRenderer::TileSize.y;

	tr->SetPos(pos);
}
