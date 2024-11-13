#pragma once
#include "Script.h"
class PlayerScript : public Script
{
public:
	PlayerScript();
	virtual ~PlayerScript();

	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hdc) override;
};

