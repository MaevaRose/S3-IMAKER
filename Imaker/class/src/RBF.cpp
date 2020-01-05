#include <iostream>
#include <class/RBF.hpp>
#include <math.h>
#include <Eigen/Dense>
#include <stdlib.h>
#include <vector>
#include <glimac/glm.hpp>

using namespace Eigen;



InterpolationFunc::InterpolationFunc(std::vector<glm::vec2> pos, VectorXd u, int indiceRBF) : position(pos), poids(u), rbfAssociate(indiceRBF) {};


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


MatrixXd InterpolationFunc::buildMatContrainte(int dim) {
    MatrixXd contraintes(dim, dim);
    for(int i=0; i<dim; i++) {
        for(int j=0; j<dim; j++) {
            contraintes(i, j) = rbfLineaire(glm::length(this->position[i] - this->position[j]), -1.f);
        }
    }
}

void InterpolationFunc::calculW(MatrixXd contraintes) {
    Eigen::ColPivHouseholderQR<Eigen::MatrixXd> dec(contraintes); 
    this->w = dec.solve(this->poids); 
}

float InterpolationFunc::calculInterpolation(glm::vec2 x) {
    float somme = 0;
    for(int i=0; i<this->poids.size(); i++) {
        somme += this->w[i] * rbfLineaire(glm::length(x - this->position[i]), 1);
    }
    return somme;
}


// int main() {
//     // Eigen::MatrixXd A(3,3); 
//     // Eigen::MatrixXd b(3,1); 
//     // Eigen::MatrixXd x(3,1); 

//     // position << 1.0,-2.0,3.0, 2.0,-4.0,1.0, 3.0,-5.0,2.0; 
//     // poids << 5.0, 5.0, 8.0; 
//     // std::cout << "Here is the matrix A:\n" << A << std::endl; 
//     // std::cout << "Here is the vector b:\n" << b << std::endl; 

    
//     // std::cout << "The solution is:\n" << x << std::endl; 

//     return 0;
// }
