#pragma once
#include "Module.h"
#include "Globals.h"
#include <vector>

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#pragma comment (lib, "Assimp/libx86/assimp.lib")

#include "Glew/Include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

struct Mesh
{
	//Index
	uint idIndex = 0; // index in VRAM
	uint numIndex = 0;
	uint* index = nullptr;

	//Vertex
	uint idVertex = 0; // unique vertex in VRAM
	uint numVertex = 0;
	float* vertex = nullptr;

	uint textureID, texHeigth, texWidth;

};

class MeshRenderer : public Module 
{
public:

	MeshRenderer(Application* app, bool start_enabled = true);
	~MeshRenderer();

	bool Start();

	bool CleanUp();

	void LoadMesh(const char* filePath);

	void FillBuffers(Mesh* mesh);

	void DrawMesh(Mesh* mesh);

	void DrawMeshes();

	void DrawNormals();

private:

	std::vector<Mesh*> meshArray;
};
