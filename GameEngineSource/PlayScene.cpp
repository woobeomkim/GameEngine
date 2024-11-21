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
#include "Cat.h"
#include "CatScript.h"
#include "BoxCollider2D.h"
#include "CollisionManager.h"
#include "Rigidbody.h"

extern Application app;

PlayScene::PlayScene()
{
}

PlayScene::~PlayScene()
{
}

void PlayScene::Init()
{
	GameObject* camera = Instantiate<GameObject>(eLayerType::Particle, Vector2(app.GetWidth() / 2, app.GetHeight() / 2));
	Camera* cameraComp = camera->AddComponent<Camera>();
	mainCamera = cameraComp;
	//camera->AddComponent<PlayerScript>();

	mPlayer = Instantiate<Player>(eLayerType::Player, Vector2(300.0f, 250.0f));
	PlayerScript* plSc = mPlayer->AddComponent<PlayerScript>();
	BoxCollider2D* collider = mPlayer->AddComponent<BoxCollider2D>();
	collider->SetOffset(Vector2(-50.0f, -50.0f));
	//Transform* playerTr = mPlayer->GetComponent<Transform>();
	//playerTr->SetScale(Vector2(1.0f, 1.0f));
	//playerTr->SetRotation(90);
	mPlayer->AddComponent<Rigidbody>();
	
	Texture* playerTex = Resources::Find<Texture>(L"Player");
	Animator* playerAnimator = mPlayer->AddComponent<Animator>();
	playerAnimator->CreateAnimation(L"Idle", playerTex,
		Vector2(2000.0f, 250.0f), Vector2(250.0f, 250.0f), Vector2::Zero, 1, 0.1f);
	playerAnimator->CreateAnimation(L"FrontGiveWater", playerTex,
		Vector2(0.0f, 2000.0f), Vector2(250.0f, 250.0f), Vector2::Zero, 12, 0.1f);
	playerAnimator->PlayAnimation(L"Idle", false);
	
	playerAnimator->GetCompleteEvent(L"FrontGiveWater") = std::bind(&PlayerScript::AttackEffect, plSc);

	Cat* cat = Instantiate<Cat>(eLayerType::Animal, Vector2(500, 500));
	BoxCollider2D* catCollider = cat->AddComponent<BoxCollider2D>();
	catCollider->SetOffset(Vector2(-50.0f, -50.0f));
	CatScript* catScript = cat->AddComponent<CatScript>();
	catScript->SetPlayer(mPlayer);
	//SpriteRenderer* sr = cat->AddComponent<SpriteRenderer>();
	Transform * tr = cat->GetComponent<Transform>();
	tr->SetScale(Vector2(1.0f, 1.0f));
	catScript->SetDest(Vector2::One);

	Animator* animator = cat->AddComponent<Animator>();
	Texture* catTexture = Resources::Find<Texture>(L"Cat");
	animator->CreateAnimation(L"DownWalk", catTexture, Vector2(0, 0), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.5f);
	animator->CreateAnimation(L"RightWalk", catTexture, Vector2(0, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.5f);
	animator->CreateAnimation(L"UpWalk", catTexture, Vector2(0, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.5f);
	animator->CreateAnimation(L"LeftWalk", catTexture, Vector2(0, 96.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.5f);
	animator->CreateAnimation(L"SitDown", catTexture, Vector2(0, 128.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.5f);
	animator->CreateAnimation(L"Grooming", catTexture, Vector2(0, 160.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.5f);
	animator->CreateAnimation(L"LayDown", catTexture, Vector2(0, 192.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.5f);
	//animator->PlayAnimation(L"SitDown", true);

	animator->CreateAnimationByFolder(L"MushroomIdle",
		L"..\\Resources\\Mushroom", Vector2::Zero, 0.1f);
	animator->PlayAnimation(L"MushroomIdle", true);

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
	CollisionManager::CollisionLayerCheck(eLayerType::Player, eLayerType::Animal, true);

	Scene::OnEnter();
}

void PlayScene::OnExit()
{
	Scene::OnExit();
}
