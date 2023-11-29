#pragma once

#include "Component.h"

#include "MathGeoLib/include/MathGeoLib.h"

class ComponentTransform : public Component {
public:

	ComponentTransform(GameObject* owner);
	~ComponentTransform();

	void OnInspector() override;

	//Get right side
	float3 GetX();
	//Get up
	float3 GetY();
	//Get forward
	float3 GetZ();

public:

	float4x4 globalTransform;
	float4x4 localTransform;

	float3 position;
	float3 rotation;
	float3 scale;

};
