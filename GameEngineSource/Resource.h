#pragma once
#include "CommonInclude.h"
#include "Entity.h"

class Resource : public Entity
{
public:
	Resource(eResourceType type);
	virtual ~Resource();

	virtual HRESULT Load(const std::wstring& path) abstract;

	const std::wstring& GetPath() { return mPath; }
	void SetPath(const std::wstring& path) { mPath = path; }
private:
	const eResourceType mType;
	std::wstring mPath;
};
