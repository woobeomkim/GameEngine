#pragma once
#include "Resource.h"
class Texture : public Resource
{
public:
	Texture();
	virtual ~Texture();

	HRESULT Load(const std::wstring& path) override;

	static Texture* Create(const std::wstring& name, UINT width, UINT height);

	Gdiplus::Image* GetImage() { return mImage; }
	eTextureType GetTextureType() { return mType; }
	HDC GetHdc() { return mHdc; }
	UINT GetWidth() { return mWidth; }
	void SetWidth(UINT width) { mWidth = width; }
	UINT GetHeight() {return mHeight;}
	void SetHeight(UINT height) { mHeight = height; }

	bool IsAlpha() { return mbAlpah; }
private:
	bool mbAlpah;
	eTextureType mType;
	Gdiplus::Image* mImage;
	HBITMAP mBitmap;
	HDC mHdc;

	UINT mWidth;
	UINT mHeight;
};

