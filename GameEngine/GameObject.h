#pragma once
#include "Globals.h"
#include "Component.h"

#include "ComponentTransform.h"
#include "ComponentMesh.h"

#include <vector>

class GameObject {
public:

	GameObject();
	~GameObject();

	void NewChild();

	void NewComponent(ComponentType type);

	void ChangeName(std::string name);

	// Return true if there's a component of specified type in vector
	bool CheckComponent(ComponentType type);

	void Inspector();

public:

	std::vector<Component*> mComponents;
	std::vector<GameObject*> mChildren;

	std::string _name;
};
