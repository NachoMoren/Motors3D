#pragma once
#include "Globals.h"

#define UID UINT64

enum class ResourceType {

	UNKNOWN = -1,
	TEXTURE,
	MESH,
	AUDIO,
	SCENE,
	BONE,
	ANIMATION
};

class Resource {

public:

	Resource(UID uid, ResourceType type);
	virtual ~Resource();
	ResourceType GetType() const;
	UID GetUID() const;
	const char* GetAssetFile() const;
	const char* GetLibraryFile() const;
	bool IsLoadedToMemory() const;
	virtual bool LoadToMemory();
	virtual bool UnloadFromMemory();
	uint GetReferenceCount() const;
	//virtual void Save(Config& config) const;
	//virtual void Load(const Config& config);
	//virtual bool LoadInMemory() = 0;

protected:

	UID uid = 0;
	std::string assetsFile;
	std::string Libraryile;
	ResourceType type = ResourceType(-1);
	uint referenceCount = 0;
};
