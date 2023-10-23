#pragma once
#ifndef MODULE_EDITOR
#define MODUEL_EDITOR

#include "Module.h"
#include "Globals.h"
#include <vector>

class ModuleEditor : public Module
{
public:

	ModuleEditor(Application* app, bool start_enabled = true);
	~ModuleEditor();

	bool Init() override;

	bool DrawEditor();
	bool CleanUp() override;

	void AddFPS(const float aFPS);
	void AddLog();

	void Configuration();

private:

	std::vector<float> mFPSLog;
	int mFPSLogSize = 50;

	std::vector<const char*> mConsoleLog;

};

#endif //MODULE_EDITOR
