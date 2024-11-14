#include "Input.h"
#include "Application.h"

extern Application app;

std::vector<Input::Key> Input::mKeys = {};
Vector2 Input::mMousePos = {};

int ASCII[(UINT)eKeyCode::END] = {
	'Q','W','E','R','T','Y','U','I','O','P',
	'A','S','D','F','G','H','J','K','L',
	'Z','X','C','V','B','N','M',
	VK_LEFT,VK_RIGHT,VK_UP,VK_DOWN,
	VK_LBUTTON,VK_MBUTTON,VK_RBUTTON,
};

void Input::Init()
{
	CreateKeys();
}

void Input::Update()
{
	UpdateKeys();
	//for (size_t i = 0; i < mKeys.size(); i++)
	//{
	//	if (GetAsyncKeyState(ASCII[i]) & 0x8000)
	//	{
	//		if (mKeys[i].bPressed)
	//		{
	//			mKeys[i].state = eKeyState::Pressed;
	//		}
	//		else
	//		{
	//			mKeys[i].state = eKeyState::Down;
	//		}
	//		mKeys[i].bPressed = true;
	//	}
	//	else
	//	{
	//		if (mKeys[i].bPressed)
	//		{
	//			mKeys[i].state = eKeyState::Up;
	//		}
	//		else
	//		{
	//			mKeys[i].state = eKeyState::None;
	//		}
	//		mKeys[i].bPressed = false;
	//	}
	//}
}

void Input::CreateKeys()
{
	for (size_t i = 0; i < (UINT)eKeyCode::END; i++)
	{
		Key key = {};
		key.keyCode = (eKeyCode)i;
		key.state = eKeyState::None;
		key.bPressed = false;
		mKeys.push_back(key);
	}
}

void Input::UpdateKeys()
{
	std::for_each(mKeys.begin(), mKeys.end(),
		[](Key& key) -> void
		{
			UpdateKey(key);
		});
}

void Input::UpdateKey(Input::Key& key)
{
	if (GetFocus())
	{
		if (IsKeyDown(key.keyCode))
		{
			UpdateKeyDown(key);
		}
		else
		{
			UpdateKeyUp(key);
		}
		getMousePositionByWindow();
	}
	else
		clearKeys();
}

bool Input::IsKeyDown(eKeyCode keyCode)
{
	return GetAsyncKeyState(ASCII[(UINT)keyCode]) & 0x8000;
}

void Input::UpdateKeyDown(Input::Key& key)
{
	if (key.bPressed)
		key.state = eKeyState::Pressed;
	else
		key.state = eKeyState::Down;
	key.bPressed = true;
}

void Input::UpdateKeyUp(Input::Key& key)
{
	if (key.bPressed)
		key.state = eKeyState::Up;
	else
		key.state = eKeyState::None;
	key.bPressed = false;
}

void Input::getMousePositionByWindow()
{
	POINT mousePos = {};
	GetCursorPos(&mousePos);
	ClientToScreen(app.GetHwnd(), &mousePos);
	mMousePos.x = mousePos.x;
	mMousePos.y = mousePos.y;
}

void Input::clearKeys()
{
	for (Key& key : mKeys)
	{
		if (key.state == eKeyState::Pressed || key.state == eKeyState::Down)
			key.state = eKeyState::Up;
		else if (key.state == eKeyState::Up)
			key.state = eKeyState::None;

		key.bPressed = false;
	}
}
