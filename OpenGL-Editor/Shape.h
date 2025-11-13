#pragma once

#include <map>
#include <string>
#include <glm.hpp>
#include <GL/glew.h>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Shader.h"

class Shape
{
private:
	std::string name;
	unsigned int VAO = 0;
	unsigned int VBO = 0;
	int vertexCount = 0;
	unsigned int drawMode = GL_TRIANGLES;

	const float sensitivity = 0.25f;

	glm::mat4 model = glm::mat4(1.0f);

public:
	Shape(const std::string& name) : name(name) { };

	void Initialize(const float vertices[], size_t vertexDataSize, unsigned int drawMode);
	const std::string& GetName() const { return name; };
	void Draw(Shader* shader, glm::mat4& view, glm::mat4& projection, float time);
	void Rotate(float x, float y);
	void Scale(glm::vec3 scale);
	void ResetTransformation();
};