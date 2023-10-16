#pragma once
#include "Globals.h"
#include "Component.h"

#include <vector>

class GameObject {
public:

	GameObject();
	~GameObject();

public:

	std::vector<Component*> mComponents;
	std::vector<GameObject*> mChildren;
}
