#version 330 core
in vec3 vertexColor;
in vec2 texCoordinates;

out vec4 FragColor;

uniform sampler2D tex0;

void main() {
    FragColor = texture(tex0, texCoordinates);
}