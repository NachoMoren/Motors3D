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

float3 ComponentTransform::GetX()
{
	return globalTransform.RotatePart().Col(0).Normalized();
}

float3 ComponentTransform::GetY()
{
	return globalTransform.RotatePart().Col(1).Normalized();
}

float3 ComponentTransform::GetZ()
{
	return globalTransform.RotatePart().Col(2).Normalized();
}
