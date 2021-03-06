#version 410 core

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;
//layout(location = 2) in vec3 aVertexColor;

//matrices de transformation
uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;
uniform vec3 cubeColor;

out vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
out vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
out vec3 vColor_vs; // Couleurs

void main() {

  //on transforme la position et la normale
  //du sommet dans des coordonnées homogènes
  vec4 vertexPosition = vec4(aVertexPosition, 1); // 1 à la fin car c'est un point
  vec4 vertexNormal = vec4(aVertexNormal, 0); // 0 à la fin car c'est un vecteur

  //on calcule les valeurs de sortie
  vPosition_vs = vec3(uMVMatrix * vertexPosition);
  vNormal_vs = vec3(uNormalMatrix * vertexNormal);

  //vColor_vs = vec3(uMVMatrix * vertexColor); // effet iridescent stylé
  //vColor_vs = aVertexColor;
  
  vColor_vs = cubeColor;

  gl_Position = uMVPMatrix * vertexPosition;
}
