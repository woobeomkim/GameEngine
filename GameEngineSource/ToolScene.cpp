#include "ToolScene.h"
#include "GameObject.h"
#include "Object.h"
#include "Tile.h"
#include "TilemapRenderer.h"
#include "Resources.h"
#include "Texture.h"
#include "Camera.h"
#include "MainCamera.h"
#include "Input.h"
#include "CameraScript.h"

ToolScene::ToolScene()
{
}

ToolScene::~ToolScene()
{
}

void ToolScene::Init()
{
	GameObject* camera = Instantiate<GameObject>(eLayerType::Particle, Vector2(344.0f, 442.0f));
	Camera* cameraComp = camera->AddComponent<Camera>();
    camera->AddComponent<CameraScript>();
    mainCamera = cameraComp;

	Tile* tile = Instantiate<Tile>(eLayerType::Tile);
	TilemapRenderer* tmr = tile->AddComponent<TilemapRenderer>();

	tmr->SetTexture(Resources::Find<Texture>(L"SpringFloor"));
	Scene::Init();
}

void ToolScene::Update()
{
	Scene::Update();
}

void ToolScene::LateUpdate()
{
	Scene::LateUpdate();

    if (Input::GetKeyDown(eKeyCode::LButton))
    {
        Vector2 pos = Input::GetMousePos();

        pos = mainCamera->CaluateTilePosition(pos);

        if (pos.x >= 0.0f && pos.y >= 0.0f)
        {
            int idxX = pos.x / TilemapRenderer::TileSize.x;
            int idxY = pos.y / TilemapRenderer::TileSize.y;

            Tile* tile = Instantiate<Tile>(eLayerType::Tile);
            TilemapRenderer* tmr = tile->AddComponent<TilemapRenderer>();
            tmr->SetTexture(Resources::Find<Texture>(L"SpringFloor"));
            tmr->SetIndex(TilemapRenderer::SelectedIndex);

            tile->SetIndexPosition(idxX, idxY);
            mTiles.push_back(tile);
        }
    }
    if (Input::GetKeyDown(eKeyCode::S))
    {
        Save();
    }

    if (Input::GetKeyDown(eKeyCode::L))
    {
        Load();
    }

}

void ToolScene::Render(HDC hdc)
{
	Scene::Render(hdc);

	for (size_t i = 0; i < 50; i++)
	{
        Vector2 pos = mainCamera->CalculatePosition(Vector2(TilemapRenderer::TileSize.x * i, 0));
		MoveToEx(hdc, pos.x, 0, nullptr);
		LineTo(hdc, pos.x, 1000);
	}

	for (size_t i = 0; i < 50; i++)
	{
        Vector2 pos = mainCamera->CalculatePosition(Vector2(0, TilemapRenderer::TileSize.y * i));
		MoveToEx(hdc, 0, pos.y, nullptr);
		LineTo(hdc, 2000, pos.y);
	}

}

void ToolScene::OnEnter()
{
    Scene::OnEnter();
}

void ToolScene::OnExit()
{
    Scene::OnExit();
}

void ToolScene::Save()
{
    OPENFILENAME ofn = {};

    wchar_t szFilePath[256] = {};

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = nullptr;
    ofn.lpstrFile = szFilePath;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 256;
    ofn.lpstrFilter = L"Tile\0*.tile\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = nullptr;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = nullptr;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (false == GetSaveFileName(&ofn))
        return;

    FILE* pFile = nullptr;
    _wfopen_s(&pFile, szFilePath, L"wb");

    for (Tile* tile : mTiles)
    {
        TilemapRenderer* tmr = tile->GetComponent<TilemapRenderer>();
        Transform* tr = tile->GetComponent<Transform>();

        Vector2 sourceIndex = tmr->GetIndex();
        Vector2 position = tr->GetPosition();

        int x = sourceIndex.x;
        fwrite(&x, sizeof(int), 1, pFile);
        int y = sourceIndex.y;
        fwrite(&y, sizeof(int), 1, pFile);

        x = position.x;
        fwrite(&x, sizeof(int), 1, pFile);
        y = position.y;
        fwrite(&y, sizeof(int), 1, pFile);
    }
    fclose(pFile);
}

void ToolScene::Load()
{
    OPENFILENAME ofn = {};

    wchar_t szFilePath[256] = {};

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = nullptr;
    ofn.lpstrFile = szFilePath;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = 256;
    ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = nullptr;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = nullptr;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (false == GetOpenFileName(&ofn))
        return;

    FILE* pFile = nullptr;
    _wfopen_s(&pFile, szFilePath, L"rb");

    while (true)
    {
        int idxX = 0;
        int idxY = 0;

        int posX = 0;
        int posY = 0;

        if (fread(&idxX, sizeof(int), 1, pFile) == NULL)
            return;
        if (fread(&idxY, sizeof(int), 1, pFile) == NULL)
            return;
        if (fread(&posX, sizeof(int), 1, pFile) == NULL)
            return;
        if (fread(&posY, sizeof(int), 1, pFile) == NULL)
            return;

        Tile* tile = Instantiate<Tile>(eLayerType::Tile, Vector2(posX, posY));
        TilemapRenderer* tmr = tile->AddComponent<TilemapRenderer>();
        tmr->SetTexture(Resources::Find<Texture>(L"SpringFloor"));
        tmr->SetIndex(Vector2(idxX, idxY));

        //tile->SetIndexPosition(posX, posY);
        mTiles.push_back(tile);
    }
    fclose(pFile);
}

LRESULT CALLBACK WndTileProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_LBUTTONDOWN:
    {
        POINT mousePos = {};
        GetCursorPos(&mousePos);
        ScreenToClient(hWnd, &mousePos);

        Vector2 mousePosition;
        mousePosition.x = mousePos.x;
        mousePosition.y = mousePos.y;

        int idxX = mousePosition.x / TilemapRenderer::OriginTileSize.x;
        int idxY = mousePosition.y / TilemapRenderer::OriginTileSize.y;

        TilemapRenderer::SelectedIndex = Vector2(idxX, idxY);
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

        Texture* texture = Resources::Find<Texture>(L"SpringFloor");

        TransparentBlt(hdc
            , 0, 0
            , texture->GetWidth()
            , texture->GetHeight()
            , texture->GetHdc()
            , 0, 0
            , texture->GetWidth()
            , texture->GetHeight()
            , RGB(255, 0, 255));

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}
