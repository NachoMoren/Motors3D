#ifndef __ModuleScene_H__
#define __ModuleScene_H__

#include "Module.h"
#include "Globals.h"

#include "GameObject.h"

#include <vector>

class ModuleScene : public Module {
public:

	ModuleScene(Application* app, bool start_enabled = true);
	~ModuleScene();

	bool Init();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

public:

	GameObject* sceneObject;
};

#endif // __ModuleScene_H__