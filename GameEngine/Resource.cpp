#include "Resource.h"

Resource::Resource(UID uid, ResourceType type)
{
}

Resource::~Resource()
{
}

ResourceType Resource::GetType() const
{
	return ResourceType();
}

UID Resource::GetUID() const
{
	return UID();
}

const char* Resource::GetAssetFile() const
{
	return nullptr;
}

const char* Resource::GetLibraryFile() const
{
	return nullptr;
}

bool Resource::IsLoadedToMemory() const
{
	return false;
}

bool Resource::LoadToMemory()
{
	return false;
}

uint Resource::GetReferenceCount() const
{
	return uint();
}
