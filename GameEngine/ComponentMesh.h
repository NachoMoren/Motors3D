#pragma once

#include "Component.h"
#include "MeshRenderer.h"

class ComponentMesh : public Component {
public:

	ComponentMesh(GameObject* owner);
	~ComponentMesh();

	void OnGui() override {

	}

private:

	Mesh* mesh;
};

