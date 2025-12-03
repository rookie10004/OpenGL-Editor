#define _CRT_SECURE_NO_WARNINGS

#include "Mesh.h"

void Mesh::Initialize(const float vertices[], size_t vertexDataSize, unsigned int drawMode)
{
	this->vertices.assign(vertices, vertices + vertexDataSize / sizeof(float));
	vertexCount = vertexDataSize / sizeof(float) / 8;
	this->drawMode = drawMode;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Größe in Bytes übergeben
	glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertices, GL_STATIC_DRAW);

	//Positionsattribut
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//Normalenattribut
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Texturenattribut
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
}

void Mesh::Draw(Shader* shader, glm::mat4& view, glm::mat4& projection, glm::vec3 cameraPosition, float time, glm::vec3 lightPosition, glm::vec3 lightColor)
{
	shader->UseShader();
	shader->SetMat4("model", model);
	shader->SetMat4("view", view);
	shader->SetMat4("projection", projection);
	shader->SetVec3("cameraPosition", cameraPosition);
	shader->SetFloat("time", time);
	shader->SetVec3("lightPosition", lightPosition);
	shader->SetVec3("lightColor", lightColor);

	glBindVertexArray(VAO);
	glDrawArrays(drawMode, 0, vertexCount);
	glBindVertexArray(0);
}

void Mesh::Rotate(float x, float y)
{
	glm::mat4 yaw = glm::rotate(glm::mat4(1.0f), glm::radians(x * sensitivity), glm::vec3(0, 1, 0));
	glm::mat4 pitch = glm::rotate(glm::mat4(1.0f), glm::radians(y * sensitivity), glm::vec3(1, 0, 0));

	model = yaw * model;
	model = pitch * model;
}

void Mesh::Scale(glm::vec3 scale)
{
	model = glm::scale(model, scale);
}

void Mesh::ResetTransformation()
{
	model = glm::mat4(1.0f);
}

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

bool Mesh::LoadOBJ(const char* path)
{
    std::ifstream file(path);
    if (!file.is_open())
        return false;

    std::vector<glm::vec3> temp_positions;
    std::vector<glm::vec3> temp_normals;
    std::vector<glm::vec2> temp_texcoords;

    std::vector<float> finalVertices;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string prefix;
        iss >> prefix;

        if (prefix == "v") {
            glm::vec3 pos;
            iss >> pos.x >> pos.y >> pos.z;
            temp_positions.push_back(pos);
        }
        else if (prefix == "vt") {
            glm::vec2 tex;
            iss >> tex.x >> tex.y;
            temp_texcoords.push_back(tex);
        }
        else if (prefix == "vn") {
            glm::vec3 normal;
            iss >> normal.x >> normal.y >> normal.z;
            temp_normals.push_back(normal);
        }
        else if (prefix == "f") {
            // Lies alle Face-Einträge (kann mehr als 3 sein)
            std::vector<std::string> faceTokens;
            std::string token;
            while (iss >> token)
                faceTokens.push_back(token);

            // Trianguliere Polygon zu Dreiecken: (0,1,2), (0,2,3), (0,3,4) ...
            for (size_t i = 1; i + 1 < faceTokens.size(); ++i) {
                std::string f[3] = { faceTokens[0], faceTokens[i], faceTokens[i + 1] };

                Vertex tri[3];

                for (int j = 0; j < 3; j++) {
                    int vi = 0, ti = 0, ni = 0;
                    // Formate: v/vt/vn, v//vn, v/vt, v
                    if (sscanf(f[j].c_str(), "%d/%d/%d", &vi, &ti, &ni) == 3) {
                        // alles ok
                    }
                    else if (sscanf(f[j].c_str(), "%d//%d", &vi, &ni) == 2) {
                        ti = 0;
                    }
                    else if (sscanf(f[j].c_str(), "%d/%d", &vi, &ti) == 2) {
                        ni = 0;
                    }
                    else if (sscanf(f[j].c_str(), "%d", &vi) == 1) {
                        ti = 0; ni = 0;
                    }

                    tri[j].position = temp_positions[vi - 1];

                    if (ti > 0)
                        tri[j].texCoord = temp_texcoords[ti - 1];
                    else
                        tri[j].texCoord = glm::vec2(0.0f);

                    if (ni > 0)
                        tri[j].normal = temp_normals[ni - 1];
                    else
                        tri[j].normal = glm::vec3(0.0f, 1.0f, 0.0f);

                    // Flatten Vertex in finalVertices
                    finalVertices.push_back(tri[j].position.x);
                    finalVertices.push_back(tri[j].position.y);
                    finalVertices.push_back(tri[j].position.z);

                    finalVertices.push_back(tri[j].normal.x);
                    finalVertices.push_back(tri[j].normal.y);
                    finalVertices.push_back(tri[j].normal.z);

                    finalVertices.push_back(tri[j].texCoord.x);
                    finalVertices.push_back(tri[j].texCoord.y);
                }
            }
        }
    }

    file.close();

    Initialize(finalVertices.data(), finalVertices.size() * sizeof(float), GL_TRIANGLES);

    return true;
}
