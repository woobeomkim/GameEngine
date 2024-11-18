#pragma once
#include "CommonInclude.h"

class Time
{
public:
	static void Init();
	static void Update();
	static void Render(HDC hdc);

	__forceinline static float DeltaTime() { return mDeltaTimeValue; }
private:
	static LARGE_INTEGER mCPUFrequency;
	static LARGE_INTEGER mPrevFrequency;
	static LARGE_INTEGER mCurrentFrequency;
	static float mDeltaTimeValue;
};

