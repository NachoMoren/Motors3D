#include "ComponentMesh.h"

ComponentMesh::ComponentMesh(GameObject* owner) : Component(ComponentType::MESH, owner)
{
	mesh = nullptr; 
}

ComponentMesh::~ComponentMesh()
{
}

void ComponentMesh::OnInspector()
{
	if (ImGui::CollapsingHeader("Mesh", ImGuiTreeNodeFlags_DefaultOpen))
	{

	}
}
