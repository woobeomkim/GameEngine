#include "TilemapRenderer.h"
#include "Texture.h"
#include "Transform.h"
#include "GameObject.h"
#include "MainCamera.h"
#include "Camera.h"

Vector2 TilemapRenderer::TileSize = Vector2::One;
Vector2 TilemapRenderer::OriginTileSize = Vector2::One;
Vector2 TilemapRenderer::SelectedIndex = Vector2::One;

TilemapRenderer::TilemapRenderer()
	: Component(eComponentType::SpriteRenderer)
	, mTexture(nullptr)
	, mSize(3.0f,3.0f)
	, mIndex(0,0)
	, mTileSize(16.0f,16.0f)
{
	TileSize = mTileSize * mSize;
	OriginTileSize = mTileSize;
}

TilemapRenderer::~TilemapRenderer()
{
}

void TilemapRenderer::Init()
{
}

void TilemapRenderer::Update()
{
}

void TilemapRenderer::LateUpdate()
{
}

void TilemapRenderer::Render(HDC hdc)
{
	if (mTexture == nullptr)
		assert(false);

	Transform* tr = GetOwner()->GetComponent<Transform>();
	Vector2 pos = tr->GetPosition();
	float rot = tr->GetRotation();
	Vector2 scale = tr->GetScale();

	pos = mainCamera->CalculatePosition(pos);

	//if (mTexture->GetTextureType() == eTextureType::Png)
	//{
	//	Gdiplus::ImageAttributes imgAtt = {};

	//	imgAtt.SetColorKey(Gdiplus::Color(230, 230, 230), Gdiplus::Color(255, 255, 255));


	//	Gdiplus::Graphics graphics(hdc);
	//	graphics.TranslateTransform(pos.x, pos.y);
	//	graphics.RotateTransform(rot);
	//	graphics.TranslateTransform(-pos.x, -pos.y);

	//	graphics.DrawImage(mTexture->GetImage()
	//		, Gdiplus::Rect
	//		(
	//			pos.x
	//			, pos.y
	//			, mTexture->GetWidth() * mSize.x * scale.x
	//			, mTexture->GetHeight() * mSize.y * scale.y
	//		)
	//		, 0, 0
	//		, mTexture->GetWidth()
	//		, mTexture->GetHeight()
	//		, Gdiplus::UnitPixel
	//		, /*&imgAtt*/ nullptr
	//	);
	//}
	if (mTexture->GetTextureType() == eTextureType::Bmp)
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
				, mTileSize.x * mSize.x * scale.x
				, mTileSize.y * mSize.y * scale.y
				, mTexture->GetHdc()
				, mIndex.x * mTileSize.x , mIndex.y * mTileSize.y
				, mTileSize.x
				, mTileSize.y
				, func);
		}
		else
		{
			TransparentBlt(hdc
				, pos.x, pos.y
				, mTileSize.x * mSize.x * scale.x
				, mTileSize.y * mSize.y * scale.y
				, mTexture->GetHdc()
				, mIndex.x * mTileSize.x, mIndex.y * mTileSize.y
				, mTileSize.x
				, mTileSize.y
				, RGB(255, 0, 255));
		}
	}
}
