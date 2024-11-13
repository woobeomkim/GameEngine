#include "Application.h"
#include "Input.h"
#include "Time.h"
#include "SceneManager.h"

Application::Application()
	:mHwnd(nullptr)
	,mHdc(nullptr)
	,mWidth(0)
	,mHeight(0)
	,mBackHdc(nullptr)
	,mBackBitmap(nullptr)
{
}

Application::~Application()
{
}

void Application::Init(HWND hwnd, UINT width, UINT height)
{
	adjustWindowRect(hwnd, width, height);
	createBuffer(width, height);
	initEtc();
}

void Application::Run()
{
	Update();
	LateUpdate();
	Render();
}

void Application::Update()
{
	Input::Update();
	Time::Update();
	SceneManager::Update();
}

void Application::LateUpdate()
{
	SceneManager::LateUpdate();
}

void Application::Render()
{
	Rectangle(mBackHdc, -1, -1, mWidth, mHeight);
	Time::Render(mBackHdc);
	SceneManager::Render(mBackHdc);
	BitBlt(mHdc, 0, 0, mWidth, mHeight, mBackHdc, 0, 0, SRCCOPY);
}

void Application::adjustWindowRect(HWND hwnd, UINT width, UINT height)
{
	mHwnd = hwnd;
	mHdc = GetDC(hwnd);

	RECT rect = { 0,0,width,height };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	mWidth = rect.right - rect.left;
	mHeight = rect.bottom - rect.top;

	SetWindowPos(mHwnd, nullptr, 0, 0, mWidth, mHeight, 0);
	ShowWindow(mHwnd, true);
}

void Application::createBuffer(UINT width, UINT height)
{
	mBackBitmap = CreateCompatibleBitmap(mHdc, width, height);
	mBackHdc = CreateCompatibleDC(mHdc);

	HBITMAP oldBitmap = (HBITMAP)SelectObject(mBackHdc, mBackBitmap);
	DeleteObject(oldBitmap);
}

void Application::initEtc()
{
	Input::Init();
	Time::Init();
	SceneManager::Init();
}
