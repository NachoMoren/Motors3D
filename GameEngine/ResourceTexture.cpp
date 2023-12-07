#include "ResourceTexture.h"

ResourceTexture::ResourceTexture(UID uid) : Resource(uid, ResourceType::TEXTURE), width(NULL), height(NULL) {
}

ResourceTexture::~ResourceTexture()
{
}

bool ResourceTexture::LoadToMemory()
{
	return false;
}

bool ResourceTexture::UnloadFromMemory()
{
	return false;
}
