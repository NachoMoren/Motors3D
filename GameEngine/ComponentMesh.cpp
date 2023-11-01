#include "ComponentMesh.h"

ComponentMesh::ComponentMesh(GameObject* owner) : Component(ComponentType::MESH, owner)
{
}

ComponentMesh::~ComponentMesh()
{
}
