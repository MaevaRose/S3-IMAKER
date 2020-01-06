#version 410 core

in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec3 vColor_vs; // Coordonnées de couleurs du sommet

//uniform sampler2D uTexture;
uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform vec3 uLightDir;
uniform vec3 uLightIntensity;

out vec3 fFragColor;

vec3 blinnPhong(){
  //Formule de blinnPhong : Li(Kd(wi˙N)+Ks(halfVector˙N)shininess)
  vec3 wi = normalize(uLightDir);
  vec3 Li = uLightIntensity/5000;
  vec3 w0 = normalize(-vPosition_vs);
  vec3 halfVector = (w0 + wi)/2;

  vec3 p1 = uKd*(dot(wi, vNormal_vs));
  vec3 p2 = uKs*pow((dot(halfVector, vNormal_vs)), uShininess);

  vec3 color = Li*(p1+p2);

  return color;
}

void main() {
  fFragColor = vColor_vs * blinnPhong();
}
