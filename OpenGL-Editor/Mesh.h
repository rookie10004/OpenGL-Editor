#pragma once

#include <map>
#include <string>
#include <vector>
#include <array>
#include <glm.hpp>
#include <GL/glew.h>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Shader.h"

class Mesh
{
private:
	std::string name;
	unsigned int VAO = 0;
	unsigned int VBO = 0;
	int vertexCount = 0;
	unsigned int drawMode = GL_TRIANGLES;
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	const float sensitivity = 0.25f;

	glm::mat4 model = glm::mat4(1.0f);

public:
	Mesh(const std::string& name) : name(name) { };

	void Initialize(const float vertices[], size_t vertexDataSize, unsigned int drawMode);
	const std::string& GetName() const { return name; };
	void Draw(Shader* shader, glm::mat4& view, glm::mat4& projection, glm::vec3 cameraPosition, float time, glm::vec3 lightPosition, glm::vec3 lightColor);
	void Rotate(float x, float y);
	void Scale(glm::vec3 scale);
	void ResetTransformation();

	std::vector<float>& GetVertices() { return vertices; }
	std::vector<unsigned int>& GetIndices() { return indices; }

	bool LoadOBJ(const char* path);
};