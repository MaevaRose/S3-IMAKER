#pragma once

#include <iostream>
#include <vector>
#include <glimac/glm.hpp>
#include <Eigen/Dense>

using namespace Eigen;



class InterpolationFunc {
    public :

    //constructor
    InterpolationFunc();
    InterpolationFunc(std::vector<glm::vec2> p, std::vector<float> u, int indiceRBF);

    //Methodes
    void calculW();
    float calculInterpolation(int posX, int posY);
    MatrixXd buildMatContrainte();
    

    private : 

    //attributs
    std::vector<glm::vec2> position;
    std::vector<float> U;
    int rbfAssociate;
    std::vector<float> w;
};