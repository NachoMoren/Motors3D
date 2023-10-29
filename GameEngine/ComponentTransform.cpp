#include "ComponentTransform.h"

ComponentTransform::ComponentTransform(std::string name, GameObject* owner) : Component(name, ComponentType::TRANSFORM, owner)
{
}

ComponentTransform::~ComponentTransform()
{
}
