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
        void setPoids(const std::vector<double> &poids);
        void setIndice(const int indiceRBF);
        void setAlpha(const float coeff);
        std::vector<double> returnContraintes() const;
        void deleteContraintes(const int indice);

        template<typename T>
        float RBF(const T &i, const T &j) const;

        void addContrainte(const int &x, const int &y, const int &z);
        MatrixXd buildMatContrainte() const;
        void calculW(const MatrixXd &contraintes);
        float calculInterpolation(const glm::vec2 &point) const;
        void drawFunc(World &world);


        private :

        //attributs
        std::vector<glm::vec2> position;
        std::vector<double> poids;
        VectorXd w;
        int rbfAssociate;
        float alpha;

    };

    float rbfLineaire(const float dist, const float alpha);
    float rbfMultiQuad(const float dist, const float alpha);
    float rbfInverseQuad(const float dist, const float alpha);
    float rbfInverseMultiQuad(const float dist, const float alpha);
    float rbfGauss(const float dist, const float alpha);



    template<typename T>
    float InterpolationFunc::RBF(const T &u, const T &v) const {
        float dist = glm::length(u - v);
        switch(this->rbfAssociate) {
            case 1:
                return rbfLineaire(dist, this->alpha);
            break;

            case 2:
                return rbfMultiQuad(dist, this->alpha);
            break;

            case 3:
                return rbfInverseQuad(dist, this->alpha);
            break;

            case 4:
                return rbfInverseMultiQuad(dist, this->alpha);
            break;

            case 5:
                return rbfGauss(dist, this->alpha);
            break;

            default :
            break;
        }
    }
}
