#include "MeshRenderer.h"

void MeshRenderer::LoadMesh(const char* filePath) {

	const aiScene* scene = aiImportFile(filePath, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{

		for (int i = 0; i < scene->mNumMeshes; i++) {

			Mesh* meshData = new Mesh;

			// copy vertices
			meshData->numVertex = scene->mMeshes[i]->mNumVertices;
			meshData->vertex = new float[meshData->numVertex * 3];
			memcpy(meshData->vertex, scene->mMeshes[i]->mVertices, sizeof(float) * meshData->numVertex * 3);
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

			meshArray.push_back(meshData); // PushBack vertexStruct in mesh array
		}

		aiReleaseImport(scene);
	}

	else {
		LOG("Error loading scene % s", filePath);
	}

}

void MeshRenderer::FillBuffers() {

	for (int i = 0; i < meshArray.size(); ++i) {

		glGenBuffers(1, (GLuint*)&(meshArray.at(i)->VBO));
		glBindBuffer(GL_ARRAY_BUFFER, meshArray.at(i)->VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * meshArray.at(i)->numVertex * 3, meshArray.at(i)->vertex, GL_STATIC_DRAW);

		glGenBuffers(1, (GLuint*)&(meshArray.at(i)->EBO));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshArray.at(i)->EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * meshArray.at(i)->numIndex * 3, meshArray.at(i)->index, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}
}

void MeshRenderer::DrawMeshes() {

	for (int i = 0; i < meshArray.size(); ++i) {

		glBindBuffer(GL_ARRAY_BUFFER, meshArray[i]->VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshArray[i]->EBO);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, NULL);
		glDrawElements(GL_TRIANGLES, meshArray[i]->numIndex, GL_UNSIGNED_INT, NULL);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	}

}
