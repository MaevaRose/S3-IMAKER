#pragma once

#include <iostream>
#include <vector>
#include <glimac/glm.hpp>
#include <Eigen/Dense>
#include <stdlib.h>

using namespace Eigen;



class InterpolationFunc {
    public :

    //constructor
    InterpolationFunc();
    InterpolationFunc(std::vector<glm::vec2> p, VectorXd u, int indiceRBF);

    //Methodes
    void calculW(MatrixXd contraintes);
    float calculInterpolation(glm::vec2 x);
    MatrixXd buildMatContrainte(int dim);
    

    private : 

    //attributs
    std::vector<glm::vec2> position;
    VectorXd poids;
    int rbfAssociate;
    VectorXd w;
};