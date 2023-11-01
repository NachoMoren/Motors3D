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

	Component(ComponentType type, GameObject* owner) : _type(type), _owner(owner)  {
	
		_name = "";
		active = true;
	};
	Component() {

	};

	~Component() {};

	void Enable() { active = true; };
	void Disable() { active = false; };

	virtual void Update() {};

	Component* CreateComponent(ComponentType type, GameObject* owner) {

		/*Component* component = nullptr;

		switch (type)
		{
		case ComponentType::UNKNOWN:
			break;
		case ComponentType::TRANSFORM:
			component = new ComponentTransform(owner);
			break;
		case ComponentType::MESH:
			component = new ComponentMesh(owner);
			break;
		case ComponentType::MATERIAL:
			break;
		case ComponentType::LIGHT:
			break;
		default:
			break;
		}*/
	}


	virtual void OnGui() {}; //Override

public:

	std::string _name;
	ComponentType _type;
	GameObject* _owner;
	bool active;



};
