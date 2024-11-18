#pragma once
#include "CommonInclude.h"

class Application
{
public:
	Application();
	~Application();

	void Init(HWND hwnd , UINT width , UINT height);
	void Run();
	void Update();
	void LateUpdate();
	void Render();
	void Release();
	void Destroy();

	HDC GetMainHdc() { return mHdc; }
	UINT GetWidth() { return mWidth;}
	UINT GetHeight() { return mHeight;}
	HWND GetHwnd() { return mHwnd; }

private:
	void adjustWindowRect(HWND hwnd, UINT width, UINT height);
	void createBuffer(UINT width, UINT height);
	void initEtc();
	void clearRenderTarget();
private:
	HWND mHwnd;
	HDC mHdc;
	UINT mWidth;
	UINT mHeight;
	HDC mBackHdc;
	HBITMAP mBackBitmap;
};

