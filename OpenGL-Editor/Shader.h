#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
private:
	unsigned int shaderProgram;

public:
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = NULL);
	~Shader();

	void UseShader();

	void SetBool(const std::string& name, bool value) const;
	void SetInt(const std::string& name, int value) const;
	void SetFloat(const std::string& name, float value) const;

	unsigned int GetID();
};