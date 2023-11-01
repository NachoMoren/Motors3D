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

}

void GameObject::ChangeName(std::string name)
{
	_name = name;
}
