#pragma once
#include "SceneManager.h"
#include "PlayScene.h"
#include "TitleScene.h"

void LoadScenes()
{
	SceneManager::CreateScene<PlayScene>(L"PlayScene");
	SceneManager::CreateScene<TitleScene>(L"TitleScene");
	SceneManager::LoadScene(L"PlayScene");
}