#pragma once
#include "CommonInclude.h"

enum class eKeyState
{
	Down,
	Pressed,
	Up,
	None,
};

enum class eKeyCode
{
	Q,W,E,R,T,Y,U,I,O,P,
	A,S,D,F,G,H,J,K,L,
	Z,X,C,V,B,N,M,
	Left,Right,Up,Down,
	END,
};

class Input
{
	struct Key
	{
		eKeyState state;
		eKeyCode keyCode;
		bool bPressed;
	};
public:
	static void Init();
	static void Update();

	static bool GetKeyDown(eKeyCode keyCode) { return mKeys[(UINT)keyCode].state == eKeyState::Down; }
	static bool GetKeyUp(eKeyCode keyCode){ return mKeys[(UINT)keyCode].state == eKeyState::Up; }
	static bool GetKey(eKeyCode keyCode){ return mKeys[(UINT)keyCode].state == eKeyState::Pressed; }
private:
	static void CreateKeys();
	static void UpdateKeys();
	static void UpdateKey(Input::Key& key);
	static bool IsKeyDown(eKeyCode keyCode);
	static void UpdateKeyDown(Input::Key& key);
	static void UpdateKeyUp(Input::Key& key);
private:
	static std::vector<Key> mKeys;
};

