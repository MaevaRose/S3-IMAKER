#include <iostream>
#include <class/RBF.hpp>

InterpolationFunc::InterpolationFunc(std::vector<glm::vec3> p, std::vector<float> u, int indiceRBF) : P(p), U(u), rbfAssociate(indiceRBF) {};

void InterpolationFunc::calculW() {
    for(int i=0; i<this->U.size(); i++) {

    }
}

float InterpolationFunc::calculInterpolation(int posX, int posY) {
    float somme = 0;
    for(int i=0; i<this->U.size(); i++) {
        somme += this->w[i] * distance(posX, P[i][0], posY, P[i][1]); //Mettre les bons indices pour P
    }
    return somme;
}