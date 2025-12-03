#define STB_IMAGE_IMPLEMENTATION

#include "Texture.h"

Texture::Texture(const char* imagePath, int texType, int slot, int format, int pixelType)
{
	type = texType;

	int widthImage, heightImage, numberColorChannel;

	stbi_set_flip_vertically_on_load(true);

	unsigned char* bytes = stbi_load(imagePath, &widthImage, &heightImage, &numberColorChannel, 4);

	// Generates an OpenGL texture object
	glGenTextures(1, &ID);

	// Assigns the texture to a Texture Unit
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	// Configures the type of algorithm that is used to make the image smaller or bigger
	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Configures the way the texture repeats (if it does at all)
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(texType, 0, GL_RGBA, widthImage, heightImage, 0, format, pixelType, bytes);

	// Generates MipMaps
	glGenerateMipmap(texType);

	// Deletes the image data as it is already in the OpenGL Texture object
	stbi_image_free(bytes);

	// Unbinds the OpenGL Texture object so that it can't accidentally be modified
	glBindTexture(texType, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}

void Texture::texUnit(Shader* shader, const char* uniform, unsigned int unit)
{
	// Gets the location of the uniform
	GLuint texUni = glGetUniformLocation(shader->GetID(), uniform);
	// Shader needs to be activated before changing the value of a uniform
	shader->UseShader();
	// Sets the value of the uniform
	glUniform1i(texUni, unit);
}

void Texture::Bind()
{
	glBindTexture(type, ID);
}
