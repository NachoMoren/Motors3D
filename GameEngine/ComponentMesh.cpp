#include "ComponentMesh.h"

ComponentMesh::ComponentMesh(std::string name, GameObject* owner) : Component(name, ComponentType::MESH, owner)
{
}

ComponentMesh::~ComponentMesh()
{
}
