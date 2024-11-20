#pragma once
#include "Script.h"
class CameraScript : public Script
{
public:
	CameraScript();
	virtual ~CameraScript();

	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hdc) override;
};

