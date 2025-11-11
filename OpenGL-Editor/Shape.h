#pragma once

#include <map>
#include <string>
#include <glm.hpp>
#include <GL/glew.h>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Shader.h"

class Shape;

struct ShapeData {
	unsigned int VAO;
	unsigned int VBO;
	int vertexCount;
	unsigned int drawMode;
	Shape* shape = nullptr;
};

class Shape
{
private:
	std::string name;

	const float sensitivity = 0.1f;

	glm::mat4 model = glm::mat4(1.0f);

public:
	Shape(const std::string& name) : name(name) { };

	ShapeData Initialize(const float vertices[], size_t vertexDataSize, unsigned int drawMode);
	const std::string& GetName() const { return name; };
	void Draw(Shader* shader, glm::mat4& view, glm::mat4& projection);
	void Rotate(float x, float y);
	void Translate(float x, float y);
	void Scale(glm::vec3 scale);
	void ResetTransformation();
};