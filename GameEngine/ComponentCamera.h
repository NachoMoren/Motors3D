#pragma once

#include "Component.h"

#include"MathGeoLib/include/Geometry/Frustum.h"

class ComponentCamera : public Component {
public:

	ComponentCamera(GameObject* owner);
	~ComponentCamera();

	void OnInspector() override;


	void Update(float dt) override;

	void LookAt(float3 pos);

public:

	Frustum frustum;

};

