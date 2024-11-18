#pragma once
#include "Scene.h"

class DontDestroyOnLoad : public Scene
{
public:
	DontDestroyOnLoad();
	virtual ~DontDestroyOnLoad();

	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hdc) override;

	void OnEnter() override;
	void OnExit() override;
};

