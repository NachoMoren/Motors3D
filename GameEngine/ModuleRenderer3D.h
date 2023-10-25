#pragma once
#include "Module.h"
#include "Globals.h"
#include "Light.h"

#include "MathGeoLib/include/Math/float3x3.h"
#include "MathGeoLib/include/Math/float4x4.h"
#include "Primitive.h"

//todo: REMOVE this before 1st delivery!!
#include "glmath.h"


#include "MeshRenderer.h"
#include "TextureImporter.h"

#define MAX_LIGHTS 8

#define CHECKERS_HEIGHT 64
#define CHECKERS_WIDTH 64

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void OnResize(int width, int height);
	void CheckerTexture(); 
	void DrawCheckersCube();

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	CPlane Grid;
	
	//You won't need this after using Frustum
	mat4x4 ProjectionMatrix;

	//tes tvar
	MeshRenderer* mRenderer;

	TextureImporter* tImporter; 

	GLubyte checkerImage[CHECKERS_HEIGHT][CHECKERS_WIDTH][4];
	GLuint checkerTexture;

	uint frameBuffer; 
	uint colorBuffer; 
	uint renderBuffer; 
};