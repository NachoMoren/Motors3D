#include "ComponentTransform.h"

ComponentTransform::ComponentTransform(GameObject* owner) : Component(ComponentType::TRANSFORM, owner)
{
}

ComponentTransform::~ComponentTransform()
{
}
