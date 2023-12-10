#include "ComponentMesh.h"
#include "GameObject.h"

ComponentMesh::ComponentMesh(GameObject* owner) : Component(ComponentType::MESH, owner)
{
	mesh = nullptr; 
	active = true; 
}

ComponentMesh::~ComponentMesh()
{

}

void ComponentMesh::OnInspector()
{
	if (ImGui::CollapsingHeader("Geometry", ImGuiTreeNodeFlags_DefaultOpen))
	{
		
		ImGui::Checkbox("##meshEnabled", &active);
		ImGui::SameLine();
		ImGui::Text("Active");

		ImGui::SameLine();
		if (ImGui::Button("Delete Component")) {
			_owner->RemoveComponent(this);
		}
		if (mesh != nullptr) {
			ImGui::LabelText("##%f", "Vertices:");
			ImGui::SameLine();
			ImGui::Text("%d", mesh->numVertex);

			ImGui::LabelText("##%f", "Indexes:");
			ImGui::SameLine();
			ImGui::Text("%d", mesh->numIndex);
		}
		else {
			ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "No mesh data found");
		}
		
	}
}
