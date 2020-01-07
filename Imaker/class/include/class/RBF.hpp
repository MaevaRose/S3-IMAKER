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
        InterpolationFunc(std::vector<glm::vec2> p, std::vector<double> u, int indiceRBF, float coeff);

        //Methodes
        void setPoids(std::vector<double> poids);
        float RBF(int i, int j);
        void addContrainte(int x, int y, int z);
        MatrixXd buildMatContrainte();
        void calculW(MatrixXd contraintes);
        float calculInterpolation(glm::vec2 point);
        void drawFunc(World &world);
        

        private : 

        //attributs
        std::vector<glm::vec2> position;
        std::vector<double> poids;
        VectorXd w;
        int rbfAssociate;
        float alpha;
    };

    float rbfLineaire(float dist, float alpha);
    float rbfMultiQuad(float dist, float alpha);
    float rbfInverseQuad(float dist, float alpha);
    float rbfInverseMultiQuad(float dist, float alpha);
    float rbfGauss(float dist, float alpha);

    
}