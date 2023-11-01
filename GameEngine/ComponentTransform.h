#pragma once

#include "Component.h"

#include "MathGeoLib/include/MathGeoLib.h"

class ComponentTransform : public Component {
public:

	ComponentTransform(GameObject* owner);
	~ComponentTransform();

	void OnInspector() override;

private:

	float4x4 matrix;

	float3 position;
	float3 rotation;
	float3 scale;

};
