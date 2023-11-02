#pragma once
#ifndef MODULE_EDITOR
#define MODUEL_EDITOR

#include "Module.h"
#include "Globals.h"
#include <vector>
#include <string>

class ModuleEditor : public Module
{
public:

	ModuleEditor(Application* app, bool start_enabled = true);
	~ModuleEditor();

	bool Init() override;

	bool DrawEditor();
	bool CleanUp() override;

	void AddFPS(const float aFPS);
	void AddLog(const std::string& str);

	void Configuration();

	ImVec4 ColToImVec(const Color& color);

	const char* GetSystemData();

	int GetUsage();
	int GetBudget();
	int GetReserved();
	int GetAvailable();
	

private:
	SDL_version version; 
	std::vector<float> mFPSLog;
	std::string systemData; 
	int mFPSLogSize = 50;


};

#endif //MODULE_EDITOR
