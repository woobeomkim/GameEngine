#pragma once
#include "SceneManager.h"
#include "PlayScene.h"
#include "TitleScene.h"
#include "ToolScene.h"

void LoadScenes()
{
	SceneManager::CreateScene<PlayScene>(L"PlayScene");
	SceneManager::CreateScene<TitleScene>(L"TitleScene");

	SceneManager::CreateScene<ToolScene>(L"ToolScene");
	SceneManager::LoadScene(L"PlayScene");
}