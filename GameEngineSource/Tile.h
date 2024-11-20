#pragma once
#include "GameObject.h"

class Tile : public GameObject
{
public:
	Tile();
	virtual ~Tile();

	void Init() override;
	void Update() override;
	void LateUpdate() override;
	void Render(HDC hdc) override;

	void SetIndexPosition(int x, int y);
};

