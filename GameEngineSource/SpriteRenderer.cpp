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
	Vector2 scale = tr->GetScale();
	float rot = tr->GetRotation();
	
	pos = mainCamera->CalculatePosition(pos);

	if (mTexture->GetTextureType() == eTextureType::Png)
	{
		Gdiplus::ImageAttributes imgAtt = {};

		imgAtt.SetColorKey(Gdiplus::Color(230, 230, 230), Gdiplus::Color(255, 255, 255));


		Gdiplus::Graphics graphics(hdc);
		graphics.TranslateTransform(pos.x, pos.y);
		graphics.RotateTransform(rot);
		graphics.TranslateTransform(-pos.x, -pos.y);
		
		graphics.DrawImage(mTexture->GetImage()
			, Gdiplus::Rect
			(
				pos.x
				, pos.y
				, mTexture->GetWidth() * mSize.x * scale.x
				, mTexture->GetHeight() * mSize.y * scale.y
			)
			, 0, 0
			, mTexture->GetWidth()
			, mTexture->GetHeight()
			, Gdiplus::UnitPixel
			, /*&imgAtt*/ nullptr
		);
	}
	else if (mTexture->GetTextureType() == eTextureType::Bmp)
	{
		if (mTexture->IsAlpha())
		{
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = AC_SRC_ALPHA;
			func.SourceConstantAlpha = 255;

			AlphaBlend(hdc
				, pos.x
				, pos.y
				, mTexture->GetWidth() * mSize.x * scale.x
				, mTexture->GetHeight() * mSize.y * scale.y
				, mTexture->GetHdc()
				, 0, 0
				, mTexture->GetWidth()
				, mTexture->GetHeight()
				, func);
		}
		else
		{
			TransparentBlt(hdc
				, pos.x, pos.y
				, mTexture->GetWidth() * mSize.x * scale.x
				, mTexture->GetHeight() * mSize.y * scale.y
				, mTexture->GetHdc()
				, 0, 0
				, mTexture->GetWidth()
				, mTexture->GetHeight()
				, RGB(255, 0, 255));
		}
	}
}
