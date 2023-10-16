#pragma once

#include "Globals.h"
#include <string>


class GameObject;

class Component {
public:

	Component();
	~Component();

	void OnGui(); //Override

public:

	std::string name;

	bool active;



};
