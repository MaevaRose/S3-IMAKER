#version 330 core

in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec3 vColor_vs; // Coordonnées de couleurs du sommet

uniform vec3 uLightDir;
uniform vec3 uLightPos;
uniform vec3 uLightIntensity;

out vec3 fFragColor;

void main() {
	vec3 color = vColor_vs;

	vec3 dirBetweenPointLightAndCurrentPixel = normalize(vPosition_vs-uLightPos);

	float luminosityDirLight = max(-dot(vNormal_vs, uLightDir), 0.);
	float d = length(vPosition_vs-uLightPos);
	float luminosityPointLight = max(-dot(vNormal_vs, dirBetweenPointLightAndCurrentPixel  ), 0.)/d/d;

	float totalLuminosity = min(luminosityDirLight + luminosityPointLight, 1.); // on s'assure que la luminosité ne dépasse pas 1
	fFragColor = vec3(color * totalLuminosity)*uLightIntensity;
}
