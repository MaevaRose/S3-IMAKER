#version 410 core

layout(location = 0) in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
layout(location = 1) in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
layout(location = 2) in vec3 vColor_vs; // Coordonnées de texture du sommet

out vec3 fFragColor;

void main() {
  fFragColor = vColor_vs;
}
