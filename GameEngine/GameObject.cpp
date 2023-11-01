#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::NewChild()
{
	GameObject* gameObject = new GameObject();
	mChildren.push_back(gameObject);
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
