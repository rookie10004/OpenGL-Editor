#version 330 core

in vec2 texCoordinates;
in vec3 Normal;
in vec3 currentPosition;

out vec4 FragColor;

uniform sampler2D tex0;
uniform vec3 lightColor = vec3(1.0, 0.9, 0.8);
uniform vec3 lightPosition = vec3(0.5f, 0.7f, 1.0f);

void main() {
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPosition - currentPosition);

	float diffuse = max(dot(normal, lightDirection), 0.0f);
	float ambient = 0.2f;

	FragColor = texture(tex0, texCoordinates) * vec4(lightColor, 1.0f) * (diffuse + ambient);
//
//	if(FragColor.r < 0.5)
//	discard;
}