#include "PlayScene.h"
#include "Player.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "Input.h"
#include "SceneManager.h"
#include "Object.h"
#include "Texture.h"
#include "Resource.h"
#include "Resources.h" 
#include "Camera.h"
#include "MainCamera.h"
#include "Application.h"
#include "PlayerScript.h"
#include "Animation.h"
#include "Animator.h"

extern Application app;

PlayScene::PlayScene()
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Init()
{
		

	GameObject* camera = Instantiate<GameObject>(eLayerType::None, Vector2(app.GetWidth() / 2, app.GetHeight() / 2));
	Camera* cameraComp = camera->AddComponent<Camera>();
	mainCamera = cameraComp;
	//camera->AddComponent<PlayerScript>();

	mPlayer = Instantiate<Player>(eLayerType::Player);
	mPlayer->AddComponent<PlayerScript>();
	
	Texture* catTexture = Resources::Find<Texture>(L"Cat");
	Animator* animator = mPlayer->AddComponent<Animator>();
	animator->CreateAnimation(L"CatFrontMove", catTexture, Vector2(0, 0), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.5f);

	animator->PlayAnimation(L"CatFrontMove", true);
	
	Scene::Init();
}

void PlayScene::Update()
{
	Scene::Update();
}

void PlayScene::LateUpdate()
{
	Scene::LateUpdate();
	if (Input::GetKeyDown(eKeyCode::N))
	{
		SceneManager::LoadScene(L"TitleScene");
	}
}

void PlayScene::Render(HDC hdc)
{
	Scene::Render(hdc);
}

void PlayScene::OnEnter()
{
	Transform* tr = mPlayer->GetComponent<Transform>();
	tr->SetPos(Vector2(100.0f, 100.0f));
}

void PlayScene::OnExit()
{
	//Transform* tr = bg->GetComponent<Transform>();
	//tr->SetPos(Vector2(0, 0));
}
