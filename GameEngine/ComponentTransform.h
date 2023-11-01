#pragma once

#include "Component.h"

#include "glmath.h"

class ComponentTransform : public Component {
public:

	ComponentTransform(GameObject* owner);
	~ComponentTransform();

	void OnGui() override {

	}

private:

	mat4x4 matrix;

	vec3 position;
	vec3 rotation;
	vec3 scale;

};
