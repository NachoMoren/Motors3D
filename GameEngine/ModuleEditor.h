#pragma once
#ifndef MODULE_EDITOR
#define MODUEL_EDITOR

#include "Module.h"
#include "Globals.h"
#include <vector>
#include <string>

class GameObject; 
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
	void ConsoleWindow(); 

	void Configuration();

	ImVec4 ColToImVec(const Color& color);

	const char* GetSystemData();

	int GetUsage();
	int GetBudget();
	int GetReserved();
	void About();
	void Hierarchy();
	int GetAvailable();
	
	bool isWireframe;
	bool showConsole; 
	bool showConfig; 
	bool showAbout; 
	bool showHierarchy; 
	bool showInspector; 
private:
	SDL_version version; 
	std::vector<float> mFPSLog;
	std::string systemData; 
	int mFPSLogSize = 50;

	const char* cubePath;
	const char* spherePath;
	const char* conePath;
	const char* cylinderPath;


};

#endif //MODULE_EDITOR
