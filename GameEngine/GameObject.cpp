#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(std::string name) : _name(name)
{
}

GameObject::~GameObject()
{
}

void GameObject::NewChild(GameObject* go)
{
	mChildren.push_back(go);
	go->SetParent(this);
}

void GameObject::NewComponent(ComponentType type)
{
	Component* component = nullptr;

	switch (type)
	{
	case ComponentType::UNKNOWN:
		break;
	case ComponentType::TRANSFORM:
		component = new ComponentTransform(this);
		break;
	case ComponentType::MESH:
		component = new ComponentMesh(this);
		break;
	case ComponentType::MATERIAL:
		break;
	case ComponentType::LIGHT:
		break;
	default:
		break;
	}

	if (!CheckComponent(type))
		mComponents.push_back(component);
	else
		LOG("Can't create duplicate Component");
}

void GameObject::SetParent(GameObject* parent)
{
	this->mParent = parent; 
}

void GameObject::Reparent(GameObject* newParent) {
	if (newParent != nullptr) {
		mParent->RemoveChild(this);
		mParent = newParent; 
		newParent->NewChild(this);
	}
}

void GameObject::RemoveChild(GameObject* child)
{
	for (uint i = 0; i < mChildren.size(); i++) {
		if (mChildren[i] == child) {
			mChildren.erase(mChildren.begin() + i);
		}
	}
}

void GameObject::ChangeName(std::string name)
{
	_name = name;
}

bool GameObject::CheckComponent(ComponentType type)
{
	bool ret = false;

	for (int i = 0; i < mComponents.size(); i++) {

		if (mComponents.at(i)->_type == type) ret = true;
	}

	return ret;
}

void GameObject::Inspector()
{
	for (int i = 0; i < mComponents.size(); i++) {

		mComponents.at(i)->OnInspector();
	}
}
