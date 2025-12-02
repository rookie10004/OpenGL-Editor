#version 330 core

in vec2 texCoordinates;
in vec3 Normal;
in vec3 currentPosition;

out vec4 FragColor;

uniform sampler2D tex0;

uniform vec3 lightColor;
uniform vec3 lightPosition;
uniform vec3 cameraPosition;

void main() {
	float ambient = 0.25f;
	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPosition - currentPosition);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 0.5f;
	vec3 viewDirection = normalize(cameraPosition - currentPosition);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specularAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 8);
	float specular = specularAmount * specularLight;

	FragColor = texture(tex0, texCoordinates) * vec4(lightColor, 1.0f) * (diffuse + specular + ambient);

//	if(FragColor.r < 0.5) discard;
}