#include "Shape.h"

ShapeData Shape::Initialize(const float vertices[], size_t vertexDataSize, unsigned int drawMode)
{
	ShapeData data;
	data.vertexCount = vertexDataSize / sizeof(float) / 6;
	data.drawMode = drawMode;

	glGenVertexArrays(1, &data.VAO);
	glGenBuffers(1, &data.VBO);

	glBindVertexArray(data.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, data.VBO);
	//Größe in Bytes übergeben
	glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertices, GL_STATIC_DRAW);

	//Positionsattribut
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Farbattribut
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);

	return data;
}

void Shape::Rotate(float x, float y)
{

}
