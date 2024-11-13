#pragma once
#include "Scene.h"
class TitleScene : public Scene
{
public:
	TitleScene();
	virtual ~TitleScene();

	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hdc) override;
};

