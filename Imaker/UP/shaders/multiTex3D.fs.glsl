#version 410 core

layout(location = 0) in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
layout(location = 1) in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
layout(location = 2) in vec2 vTexCoords; // Coordonnées de texture du sommet

uniform sampler2D uTexture;
uniform sampler2D uTexture2;

out vec3 fFragColor;

void main() {
  vec3 tex1 =  texture(uTexture, vTexCoords).xyz;
  vec3 tex2 = texture(uTexture2, vTexCoords).xyz;
  fFragColor = tex1 + tex2;
}
