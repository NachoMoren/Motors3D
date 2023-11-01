#include "ComponentTransform.h"

ComponentTransform::ComponentTransform(GameObject* owner) : Component(ComponentType::TRANSFORM, owner)
{
}

ComponentTransform::~ComponentTransform()
{
}

void ComponentTransform::OnInspector()
{
	if (ImGui::CollapsingHeader("Transform"))
	{
		ImGui::InputFloat3("Position", position.ptr());
		ImGui::InputFloat3("Rotation", rotation.ptr());
		ImGui::InputFloat3("Scale", scale.ptr());
	}
}
