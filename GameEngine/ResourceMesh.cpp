#include "ResourceMesh.h"

ResourceMesh::ResourceMesh(UID uid) : Resource(uid, ResourceType::MESH) {
}

ResourceMesh::~ResourceMesh()
{
}

bool ResourceMesh::LoadToMemory()
{
	return false;
}

void ResourceMesh::RegenerateBuffers(bool init)
{
}

bool ResourceMesh::UnloadFromMemory()
{
	return false;
}

void ResourceMesh::RenderMesh(uint textureID)
{
}

float3 ResourceMesh::GetVectorFromIndex(float* startValue)
{
	return float3();
}
