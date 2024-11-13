#include "SpriteRenderer.h"
#include "Transform.h"
#include "Component.h"
#include "GameObject.h"
#include "Texture.h"
#include "Camera.h"
#include "MainCamera.h"


SpriteRenderer::SpriteRenderer()
	: Component(eComponentType::SpriteRenderer)
	, mTexture(nullptr)
	, mSize(Vector2::One)
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::Init()
{
}

void SpriteRenderer::Update()
{
}

void SpriteRenderer::LateUpdate()
{
}

void SpriteRenderer::Render(HDC hdc)
{
	if (mTexture == nullptr)
		assert(false);

	Transform* tr = GetOwner()->GetComponent<Transform>();
	Vector2 pos = tr->GetPosition();

	pos = mainCamera->CalculatePosition(pos);

	if (mTexture->GetTextureType() == eTextureType::Png)
	{
		Gdiplus::Graphics graphics(hdc);
		graphics.DrawImage(mTexture->GetImage(), Gdiplus::Rect(pos.x, pos.y, mTexture->GetWidth(), mTexture->GetHeight()));
	}
	else if (mTexture->GetTextureType() == eTextureType::Bmp)
	{
		TransparentBlt(hdc
			, pos.x, pos.y
			, mTexture->GetWidth() * mSize.x
			, mTexture->GetHeight() * mSize.y
			, mTexture->GetHdc()
			, 0, 0
			, mTexture->GetWidth()
			, mTexture->GetHeight()
			, RGB(255, 0, 255));
	}
}
