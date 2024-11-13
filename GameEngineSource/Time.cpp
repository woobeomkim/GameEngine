#include "Time.h"

LARGE_INTEGER Time::mCPUFrequency = {};
LARGE_INTEGER Time::mPrevFrequency = {};
LARGE_INTEGER Time::mCurrentFrequency = {};
float Time::mDeltaTimeValue = 0.0f;

void Time::Init()
{
	QueryPerformanceFrequency(&mCPUFrequency);
	QueryPerformanceCounter(&mPrevFrequency);
}

void Time::Update()
{
	QueryPerformanceCounter(&mCurrentFrequency);

	float diff = static_cast<float>(mCurrentFrequency.QuadPart - mPrevFrequency.QuadPart);
	mDeltaTimeValue = diff / static_cast<float>(mCPUFrequency.QuadPart);
	
	mPrevFrequency = mCurrentFrequency;
}

void Time::Render(HDC hdc)
{
	static float Time = 0.0f;
	Time += mDeltaTimeValue;
	float fps = 1.0f / mDeltaTimeValue;

	wchar_t str[50] = L"";
	swprintf_s(str, 50, L"Time : %d", (int)fps);
	int len = wcslen(str);
	TextOut(hdc, 0, 0, str, len);

}
