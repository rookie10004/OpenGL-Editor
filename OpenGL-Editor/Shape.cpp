#include "Shape.h"

ShapeData Shape::Initialize(const float vertices[], size_t vertexDataSize, unsigned int drawMode)
{
	ShapeData data;
	data.vertexCount = vertexDataSize / sizeof(float) / 6;
	data.drawMode = drawMode;
	data.shape = this;

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

void Shape::Draw(Shader* shader, glm::mat4& view, glm::mat4& projection)
{
	shader->UseShader();
	shader->SetMat4("model", model);
	shader->SetMat4("view", view);
	shader->SetMat4("projection", projection);
}

void Shape::Rotate(float x, float y)
{
	glm::mat4 yaw = glm::rotate(glm::mat4(1.0f), glm::radians(x * sensitivity), glm::vec3(0, 1, 0));
	glm::mat4 pitch = glm::rotate(glm::mat4(1.0f), glm::radians(y * sensitivity), glm::vec3(1, 0, 0));

	model = yaw * model;
	model = pitch * model;
}
