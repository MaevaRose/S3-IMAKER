#pragma once

#include <iostream>
#include <vector>
#include <glimac/glm.hpp>
#include <class/World.hpp>
#include <Eigen/Dense>
#include <vector>
#include <stdlib.h>
#include <math.h>


using namespace Eigen;


namespace Imaker{
    class InterpolationFunc {
        public :

        //constructor
        InterpolationFunc();
        InterpolationFunc(std::vector<glm::vec2> p, VectorXd u, int indiceRBF);

        //Methodes
        void setPoids(VectorXd poids);
        void addContrainte(int x, int y, int z);
        MatrixXd buildMatContrainte(int dim);
        void calculW(MatrixXd contraintes);
        float calculInterpolation(glm::vec2 x);
        void drawFunc(int X, int Y, World world);
        

        private : 

        //attributs
        std::vector<glm::vec2> position;
        VectorXd poids;
        int rbfAssociate;
        VectorXd w;
    };
}