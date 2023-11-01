#pragma once

#include "Component.h"
#include "MeshRenderer.h"

class ComponentMesh : public Component {
public:

	ComponentMesh(GameObject* owner);
	~ComponentMesh();

	void OnInspector() override;

private:

	Mesh* mesh;
};

