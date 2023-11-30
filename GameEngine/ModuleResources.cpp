#include "ModuleResources.h"

ModuleResources::ModuleResources(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleResources::~ModuleResources()
{
}

bool ModuleResources::Init()
{
	return false;
}

update_status ModuleResources::PreUpdate(float dt)
{
	return update_status();
}

update_status ModuleResources::PostUpdate(float dt)
{
	return update_status();
}

bool ModuleResources::CleanUp()
{
	return false;
}
