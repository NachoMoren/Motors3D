#pragma once

#include"Resource.h"

#include"MathGeoLib\include\MathGeoLib.h"
#include"MathGeoLib/include/Math/float4x4.h"

class ResourceMesh : public Resource
{

public:
	ResourceMesh(UID uid);
	~ResourceMesh();

	bool LoadToMemory() override;
	void RegenerateBuffers(bool init = false);
	bool UnloadFromMemory() override;

	void RenderMesh(uint textureID);

	float3 GetVectorFromIndex(float* startValue);

public:
	//Index
	uint idIndex = 0; // index in VRAM
	uint numIndex = 0;
	uint* index = nullptr;

	//Vertex
	uint idVertex = 0; // unique vertex in VRAM
	uint numVertex = 0;
	float* vertex = nullptr;

};

