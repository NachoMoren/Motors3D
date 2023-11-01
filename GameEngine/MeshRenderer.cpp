#include "MeshRenderer.h"
#include "Application.h"
#include "glmath.h"
#include "Globals.h"
#include "ModuleRenderer3D.h"
#pragma comment (lib, "Assimp/libx86/assimp.lib")
#include "ImGui/backends/imgui_impl_sdl2.h"
#include "Primitive.h"

MeshRenderer::MeshRenderer(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

// Destructor
MeshRenderer::~MeshRenderer()
{}

bool MeshRenderer::Start()
{
	LOG("Creating 3D Renderer context");
	bool ret = true;

	return ret;
}

bool MeshRenderer::CleanUp()
{
	LOG("Deleting 3D Render");
	//Delete Meshes array
	for (int i = 0; i < meshArray.size(); i++) {
		delete meshArray[i];
		meshArray[i] = nullptr;
	}
	meshArray.clear();
	return true;
}

void MeshRenderer::LoadMesh(const char* filePath) {

	const aiScene* scene = aiImportFile(filePath, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{

		for (int i = 0; i < scene->mNumMeshes; i++) {

			Mesh* meshData = new Mesh();

			// copy vertices
			meshData->numVertex = scene->mMeshes[i]->mNumVertices;
			meshData->vertex = new float[meshData->numVertex * 5];

			for (int k = 0; k < meshData->numVertex; k++) {
				meshData->vertex[k * 5] = scene->mMeshes[i]->mVertices[k].x;
				meshData->vertex[k * 5 + 1] = scene->mMeshes[i]->mVertices[k].y;
				meshData->vertex[k * 5 + 2] = scene->mMeshes[i]->mVertices[k].z;

				meshData->vertex[k * 5 + 3] = scene->mMeshes[i]->mTextureCoords[0][k].x;
				meshData->vertex[k * 5 + 4] = scene->mMeshes[i]->mTextureCoords[0][k].y;

			}

			LOG("New mesh with %d vertices", meshData->numVertex);

			// copy faces
			if (scene->mMeshes[i]->HasFaces())
			{
				meshData->numIndex = scene->mMeshes[i]->mNumFaces * 3;
				meshData->index = new uint[meshData->numIndex]; // assume each face is a triangle
				for (uint j = 0; j < scene->mMeshes[i]->mNumFaces; ++j)
				{
					if (scene->mMeshes[i]->mFaces[j].mNumIndices != 3) {
						LOG("WARNING, geometry face with != 3 indices!");

					}
					else {
						memcpy(&meshData->index[j * 3], scene->mMeshes[i]->mFaces[j].mIndices, 3 * sizeof(uint));

					}
				}

			}
			FillBuffers(meshData);
			meshArray.push_back(meshData); // PushBack vertexStruct in mesh array
			


		}
	

		aiReleaseImport(scene);
	}

	else {
		LOG("Error loading scene % s", filePath);
	}

}

void MeshRenderer::FillBuffers(Mesh* mesh) {

	glEnableClientState(GL_VERTEX_ARRAY);
	glGenBuffers(1, (GLuint*)&(mesh->idVertex));
	glBindBuffer(GL_ARRAY_BUFFER, mesh->idVertex);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * mesh->numVertex * 5, mesh->vertex, GL_STATIC_DRAW);

	glGenBuffers(1, (GLuint*)&(mesh->idIndex));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->idIndex);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * mesh->numIndex, mesh->index, GL_STATIC_DRAW);

	glDisableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void MeshRenderer::DrawMesh(Mesh* mesh) {

	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->idVertex);
	glVertexPointer(3, GL_FLOAT, sizeof(float) * 5, NULL);
	glTexCoordPointer(2, GL_FLOAT, sizeof(float) * 5, (void*)(sizeof(float) * 3));
	
	//glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->idIndex);
	glDrawElements(GL_TRIANGLES, mesh->numIndex, GL_UNSIGNED_INT, NULL);

	glDisableClientState(GL_VERTEX_ARRAY);
	//glBindTexture(GL_TEXTURE_2D, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_TEXTURE_COORD_ARRAY);

	//DrawNormals();

}

void MeshRenderer::DrawMeshes()
{
	for (int i = 0; i < meshArray.size(); i++) {
		DrawMesh(meshArray[i]);
	}
}

void MeshRenderer::DrawNormals() {

	for (int i = 0; i < meshArray.size(); ++i) {

		int x, y, z;
		int nX, nY, nZ;

		x = meshArray.at(i)->vertex[(sizeof(float) * meshArray.at(i)->numVertex * 3)];
		y = meshArray.at(i)->vertex[(sizeof(float) * meshArray.at(i)->numVertex * 3) + 1];
		z = meshArray.at(i)->vertex[(sizeof(float) * meshArray.at(i)->numVertex * 3) + 2];

		nX = x / sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
		nY = y / sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
		nZ = z / sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));

		glBegin(GL_LINES);
		glVertex3f(x,y,z);
		glVertex3f(nX, nY, nZ);
		glEnd();

	}
}
