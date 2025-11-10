#pragma once

#include <map>
#include <string>
#include <glm.hpp>
#include <GL/glew.h>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

struct ShapeData {
	unsigned int VAO;
	unsigned int VBO;
	int vertexCount;
	unsigned int drawMode;
};

class Shape
{
private:
	std::string name;

public:
	Shape(const std::string& name) : name(name) { };

	ShapeData Initialize(const float vertices[], size_t vertexDataSize, unsigned int drawMode);
	const std::string& GetName() const { return name; };
	void Rotate(float x, float y);
	void Scale(glm::vec3 scale);
	void ResetScale();
};

