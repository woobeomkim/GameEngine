#pragma once
#include "Scene.h"
class PlayScene : public Scene
{
public:
	PlayScene();
	virtual ~PlayScene();

	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hdc) override;

	void OnEnter() override;
	void OnExit() override;

private:
	class Player* mPlayer;
};