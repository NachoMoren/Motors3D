#include "TextureImporter.h"


GLuint TextureImporter::ImportTexture(const char* filePath)
{
	ILuint TextureID; 
	ilGenImages(1, &TextureID);
	ilBindImage(TextureID); 
	ilLoadImage(filePath); 
	GLuint ID = ilutGLBindTexImage(); 

	ilDeleteImages(1, &TextureID);

	//glBindTexture(GL_TEXTURE_2D, 0);

	if (TextureID != NULL) {
		LOG("Texture %s loaded successfully", filePath);
	}
	else {
		LOG("Error loading the texture");
	}


	return ID; 
}

void TextureImporter::InitDevil()
{
	ilInit();
	iluInit();
	ilutInit();
	ilutRenderer(ILUT_OPENGL);
}
