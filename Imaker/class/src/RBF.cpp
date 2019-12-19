#include <iostream>
#include <class/RBF.hpp>
#include <math.h>
#include <Eigen/Dense>

using namespace Eigen;

InterpolationFunc::InterpolationFunc(std::vector<glm::vec2> p, std::vector<float> u, int indiceRBF) : P(p), U(u), rbfAssociate(indiceRBF) {};


MatrixXd InterpolationFunc::buildMatContrainte(int dim) {
    MatrixXd contraintes(dim, dim);
    for(int i=0; i<dim; i++) {
        for(int j=0; j<dim; j++) {
            comtraintes(i, j) = rbfLineaire(glm::length(this->position[i], this->position[j]), -1.)
        }
    }
}

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

float rbfLineaire(float dist, float alpha) {
    return alpha * dist;
}

float rbfMultiquad(float dist, float alpha) {
    return sqrt(1 + (alpha * dist) * (alpha * dist));
}

float rbfInverseQuad(float dist, float alpha) {
    return 1/(1 + (alpha * dist) * (alpha * dist));
}

float rbfInverseMultiquad(float dist, float alpha) {
    return 1/(sqrt(1 + (alpha * dist) * (alpha * dist)));
}

float rbfGauss(float dist, float alpha) {
    return exp(-(alpha * dist) * (alpha * dist));
}

float rbfLog(float dist, float alpha) {
    return dist * dist * log(dist/alpha);
}


int main() {
    Eigen::MatrixXd A(3,3); 
    Eigen::MatrixXd b(3,1); 
    Eigen::MatrixXd x(3,1); 

    A << 1.0,-2.0,3.0, 2.0,-4.0,1.0, 3.0,-5.0,2.0; 
    b << 5.0, 5.0, 8.0; 
    std::cout << "Here is the matrix A:\n" << A << std::endl; 
    std::cout << "Here is the vector b:\n" << b << std::endl; 

    Eigen::ColPivHouseholderQR<Eigen::MatrixXd> dec(A); 
    x = dec.solve(b); 
    std::cout << "The solution is:\n" << x << std::endl; 

    return 0;
}
