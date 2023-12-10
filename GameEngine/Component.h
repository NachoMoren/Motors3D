#pragma once

#include "Globals.h"
#include <string>

#include "ImGui/imgui.h"
#include "ImGui//backends/imgui_impl_sdl2.h"
#include "ImGui//backends/imgui_impl_opengl3.h"

class GameObject;

enum class ComponentType {

	UNKNOWN = -1,
	TRANSFORM,
	MESH,
	MATERIAL,
	LIGHT,
	CAMERA
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

	virtual void Update(float dt) {};

	virtual void OnInspector() {};

public:

	std::string _name;
	ComponentType _type;
	GameObject* _owner;
	bool active;



};
