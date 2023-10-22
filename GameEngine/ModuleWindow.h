#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "SDL/include/SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~ModuleWindow();

	bool Init();
	bool CleanUp();

	void SetTitle(const char* title);

	void UpdateSize();
	void UpdateFlags();

public:
	//The window we'll be rendering to
	SDL_Window* window;

	int width, height;

	Uint32 flags;

	//The surface contained by the window
	SDL_Surface* screen_surface;

	bool isFullscreen;
	bool isResizable;
	bool isBorderless;
	bool IsFullDesktop;
};

#endif // __ModuleWindow_H__