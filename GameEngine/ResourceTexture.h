#pragma once

#include"Resource.h"

class ResourceTexture : public Resource
{
public:
	ResourceTexture(UID uid);
	~ResourceTexture();

	bool LoadToMemory() override;
	bool UnloadFromMemory() override;

public:
	int width;
	int height;

	uint id;

};