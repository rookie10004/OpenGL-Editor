#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include "Shader.h"
#include <stb_image.h>
#include <GL/glew.h>
#include <glm.hpp>


class Texture
{
private:
	unsigned int ID;
	int type;

public:
	Texture() = default;
	Texture(const char* imagePath, int texType, int slot, int format, int pixelType);

	void texUnit(Shader* shader, const char* uniform, unsigned int unit);
	void Bind();
	void Delete();
};

#endif