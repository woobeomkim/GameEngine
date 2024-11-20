#pragma once
#include "Scene.h"

class ToolScene : public Scene
{
public:
	ToolScene();
	virtual ~ToolScene();

	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hdc) override;

	void OnEnter() override;
	void OnExit() override;

	void Save();
	void Load();

private:
	std::vector<class Tile*> mTiles;
};

LRESULT CALLBACK WndTileProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);