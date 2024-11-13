#pragma once
#include "Resource.h"
class Texture : public Resource
{
public:
	Texture();
	virtual ~Texture();

	HRESULT Load(const std::wstring& path) override;

	Gdiplus::Image* GetImage() { return mImage; }
	eTextureType GetTextureType() { return mType; }
	HDC GetHdc() { return mHdc; }
	UINT GetWidth() { return mWidth; }
	UINT GetHeight() {return mHeight;}
private:
	eTextureType mType;
	Gdiplus::Image* mImage;
	HBITMAP mBitmap;
	HDC mHdc;

	UINT mWidth;
	UINT mHeight;
};

