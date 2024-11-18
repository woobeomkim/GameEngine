#include "Resources.h"

std::map<std::wstring, Resource*> Resources::mResources = {};

void Resources::Release()
{
	for (auto& iter : mResources)
	{
		delete iter.second;
		iter.second = nullptr;
	}
}
