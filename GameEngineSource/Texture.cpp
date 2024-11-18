#include "Texture.h"
#include "Application.h"
#include "Resources.h"

extern Application app;

Texture* Texture::Create(const std::wstring& name, UINT width, UINT height)
{
    Texture* image = Resources::Find<Texture>(name);
    if (image)
        return image;

    image = new Texture();
    image->SetName(name);
    image->SetWidth(width);
    image->SetHeight(height);

    HDC hdc = app.GetMainHdc();
    HWND hwnd = app.GetHwnd();

    image->mBitmap = CreateCompatibleBitmap(hdc, width, height);
    image->mHdc = CreateCompatibleDC(hdc);

    HBRUSH transparentBrush = (HBRUSH)CreateSolidBrush(NULL_BRUSH);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, transparentBrush);

    Rectangle(hdc, -1, -1, width + 1, height + 1);

    SelectObject(hdc, oldBrush);
    DeleteObject(transparentBrush);

    image->mType = eTextureType::Bmp;

    HBITMAP oldBitmp = (HBITMAP)SelectObject(image->mHdc, image->mBitmap);
    DeleteObject(oldBitmp);

    Resources::Insert(name + L"Image", image);

    return image;
}

Texture::Texture()
    : Resource(eResourceType::Texture)
    , mbAlpah(false)
    , mType(eTextureType::End)
    , mImage(nullptr)
    , mBitmap(nullptr)
    , mHdc(nullptr)
    , mWidth(0)
    , mHeight(0)
{
}

Texture::~Texture()
{
}

HRESULT Texture::Load(const std::wstring& path)
{
    std::wstring ext
        = path.substr(path.find_last_of(L".") + 1);

    if (ext == L"bmp")
    {
        mType = eTextureType::Bmp;
        mBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
        if (mBitmap == nullptr)
            return S_FALSE;

        BITMAP info = {};
        GetObject(mBitmap, sizeof(BITMAP), &info);

        mWidth = info.bmWidth;
        mHeight = info.bmHeight;

        if (info.bmBitsPixel == 24)
            mbAlpah = false;
        else if (info.bmBitsPixel == 32)
            mbAlpah = true;

        HDC mainDC = app.GetMainHdc();
        mHdc = CreateCompatibleDC(mainDC);

        HBITMAP oldBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);
        DeleteObject(oldBitmap);
    }
    else if (ext == L"png")
    {
        mType = eTextureType::Png;
        mImage = Gdiplus::Image::FromFile(path.c_str());
        if (mImage == nullptr)
            return S_FALSE;

        mWidth = mImage->GetWidth();
        mHeight = mImage->GetHeight();
    }
    return S_OK;
}

