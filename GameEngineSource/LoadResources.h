#pragma once
#include "Texture.h"
#include "Resources.h"

void LoadResources()
{
	Resources::Load<Texture>(L"BG", L"..\\Resources\\CloudOcean.png");
	Resources::Load<Texture>(L"Cat", L"..\\Resources\\ChickenAlpha.bmp");
	Resources::Load<Texture>(L"Bubble", L"..\\Resources\\Bubble.png");
	Resources::Load<Texture>(L"MapleEffect", L"..\\Resources\\ezgif.com-gif-maker.png");
	Resources::Load<Texture>(L"Player", L"..\\Resources\\Player.bmp");
}