#pragma once
#include "Texture.h"
#include "Resources.h"

void LoadResources()
{
	Resources::Load<Texture>(L"BG", L"..\\Resources\\CloudOcean.png");
	Resources::Load<Texture>(L"Cat", L"..\\Resources\\ChickenAlpha.bmp");

}