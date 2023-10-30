#pragma once

#include "Globals.h"
#include <string>

class GameObject;

enum class ComponentType {

	UNKNOWN = -1,
	TRANSFORM,
	MESH,
	MATERIAL,
	LIGHT
};

class Component {
public:

	Component(std::string name, ComponentType type, GameObject* owner) : _name(name), _type(type), _owner(owner)  {};
	Component() {

	};

	~Component() {};

	virtual void Enable() {};
	virtual void Disable() {};

	virtual void Update() {};


	virtual void OnGui() {}; //Override

public:

	std::string _name;
	ComponentType _type;
	GameObject* _owner;
	bool active;



};
