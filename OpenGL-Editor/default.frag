#version 330 core
in vec3 vertexColor;
out vec4 FragColor;

uniform float time;

void main() {
    FragColor = vec4(vertexColor + (sin(time) * 0.5 + 0.5), 1.0f);
}