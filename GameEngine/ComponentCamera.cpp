#include "ComponentCamera.h"

#include "ComponentTransform.h"
#include "GameObject.h"

ComponentCamera::ComponentCamera(GameObject* owner) : Component(ComponentType::CAMERA, owner)
{
	frustum.type = FrustumType::PerspectiveFrustum;
	frustum.nearPlaneDistance = 1;
	frustum.farPlaneDistance = 100.f;
	frustum.front = _owner->transform->GetZ();
	frustum.up = _owner->transform->GetY();

	frustum.verticalFov = 60.0f * DEGTORAD;
	frustum.horizontalFov = 2.0f * atanf(tanf(frustum.verticalFov / 2.0f) * 1.3f);

	frustum.pos = _owner->transform->position;
}

ComponentCamera::~ComponentCamera()
{
}

void ComponentCamera::OnInspector()
{
	if (ImGui::CollapsingHeader("Camera")) {
		if (ImGui::SliderFloat) {

		}
	}

}

void ComponentCamera::Update(float dt) {


}

void ComponentCamera::LookAt(float3 pos) {

	frustum.front = (pos - frustum.pos).Normalized();
	float3 X = float3(0, 1, 0).Cross(frustum.front).Normalized();
	frustum.up = frustum.front.Cross(X);
}
