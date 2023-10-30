#pragma once

#include "Component.h"

class ComponentMesh : public Component {
public:

	ComponentMesh(std::string name, GameObject* owner);
	~ComponentMesh();

	void OnGui() override {

	}

private:


};

