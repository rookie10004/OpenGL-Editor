#include "Shape.h"

void Shape::Initialize(const float vertices[], size_t vertexDataSize, unsigned int drawMode)
{
	vertexCount = vertexDataSize / sizeof(float) / 6;
	this->drawMode = drawMode;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Größe in Bytes übergeben
	glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertices, GL_STATIC_DRAW);

	//Positionsattribut
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Farbattribut
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void Shape::Draw(Shader* shader, glm::mat4& view, glm::mat4& projection)
{
	shader->UseShader();
	shader->SetMat4("model", model);
	shader->SetMat4("view", view);
	shader->SetMat4("projection", projection);

	glBindVertexArray(VAO);
	glDrawArrays(drawMode, 0, vertexCount);
	glBindVertexArray(0);
}

void Shape::Rotate(float x, float y)
{
	glm::mat4 yaw = glm::rotate(glm::mat4(1.0f), glm::radians(x * sensitivity), glm::vec3(0, 1, 0));
	glm::mat4 pitch = glm::rotate(glm::mat4(1.0f), glm::radians(y * sensitivity), glm::vec3(1, 0, 0));

	model = yaw * model;
	model = pitch * model;
}

void Shape::Scale(glm::vec3 scale)
{
	model = glm::scale(model, scale);
}
