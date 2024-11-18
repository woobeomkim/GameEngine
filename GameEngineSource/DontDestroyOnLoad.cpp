#include "DontDestroyOnLoad.h"

DontDestroyOnLoad::DontDestroyOnLoad()
{
}

DontDestroyOnLoad::~DontDestroyOnLoad()
{
}

void DontDestroyOnLoad::Init()
{
	Scene::Init();
}

void DontDestroyOnLoad::Update()
{
	Scene::Update();
}

void DontDestroyOnLoad::LateUpdate()
{
	Scene::LateUpdate();
}

void DontDestroyOnLoad::Render(HDC hdc)
{
	Scene::Render(hdc);
}

void DontDestroyOnLoad::OnEnter()
{
	Scene::OnEnter();
}

void DontDestroyOnLoad::OnExit()
{
	Scene::OnExit();
}
