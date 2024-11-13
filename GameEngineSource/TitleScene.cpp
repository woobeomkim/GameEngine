#include "TitleScene.h"
#include "Input.h"
#include "SceneManager.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
}

void TitleScene::Update()
{
	Scene::Update();
}

void TitleScene::LateUpdate()
{
	Scene::LateUpdate();
	if (Input::GetKeyDown(eKeyCode::N))
	{
		SceneManager::LoadScene(L"PlayScene");
	}
}

void TitleScene::Render(HDC hdc)
{
	Scene::Render(hdc);
}
