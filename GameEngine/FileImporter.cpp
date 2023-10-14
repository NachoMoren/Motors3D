#include "FileImporter.h"

void FileImporter::LoadFile(const char* filePath) {
	const aiScene* scene = aiImportFile(filePath, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{

		for (int i = 0; i < scene->mNumMeshes; i++) {



			VertexData* vData = new VertexData;

			// copy vertices
			vData->numVertex = scene->mMeshes[i]->mNumVertices;
			vData->vertex = new float[vData->numVertex * 3];
			memcpy(vData->vertex, scene->mMeshes[i]->mVertices, sizeof(float) * vData->numVertex * 3);
			LOG("New mesh with %d vertices", vData->numVertex);

			// copy faces
			if (scene->mMeshes[i]->HasFaces())
			{
				vData->numIndex = scene->mMeshes[i]->mNumFaces * 3;
				vData->index = new uint[vData->numIndex]; // assume each face is a triangle
				for (uint i = 0; i < scene->mMeshes[i]->mNumFaces; ++i)
				{
					if (scene->mMeshes[i]->mFaces[i].mNumIndices != 3) {
						LOG("WARNING, geometry face with != 3 indices!");

					}
					else {
						memcpy(&vData->index[i * 3], scene->mMeshes[i]->mFaces[i].mIndices, 3 * sizeof(uint));

					}
				}
			}

			meshArray.push_back(vData); // PushBack vertexStruct in mesh array
			LoadToMemory(vData->idVertex);

		}

		aiReleaseImport(scene);
	}

	else {
		LOG("Error loading scene % s", filePath);
	}
}

void FileImporter::LoadToMemory(uint id)
{

	uint my_id = 0;
	glGenBuffers(1, (GLuint*)&(my_id));
	glBindBuffer(GL_ARRAY_BUFFER, my_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * meshArray.at(id)->numVertex * 3, meshArray.at(id)->vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/*glBindBuffer(GL_ARRAY_BUFFER, my_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * meshArray.at(id)->numVertex * 3, meshArray.at(id)->vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);*/

	glDrawArrays(GL_TRIANGLES, 0, meshArray.at(id)->numVertex);
	glDisableClientState(GL_VERTEX_ARRAY);

}
