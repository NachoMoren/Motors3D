#pragma once
#include "Globals.h"
#include "Component.h"

#include <vector>

class ComponentTransform;

class GameObject {
public:

	GameObject();
	GameObject(std::string name);
	~GameObject();

	void NewChild(GameObject* go);

	void NewComponent(ComponentType type);

	void SetParent(GameObject* parent);

	void Reparent(GameObject* newParent);

	void RemoveChild(GameObject* child);

	void ChangeName(std::string name);

	// Return true if there's a component of specified type in vector
	bool CheckComponent(ComponentType type);

	void Inspector();

public:
	GameObject* mParent; 

	GameObject* parent;
	std::vector<Component*> mComponents;
	std::vector<GameObject*> mChildren;

	std::string _name;

	ComponentTransform* transform;
};
