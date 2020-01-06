#include <iostream>
#include <class/RBF.hpp>


using namespace Eigen;


namespace Imaker{
    //RADIAL FUNCTIONS _____________________________________________________________

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


    //INTERPOLATION FUNC CLASS_______________________________________________________

    InterpolationFunc::InterpolationFunc(std::vector<glm::vec2> pos, VectorXd u, int indiceRBF) : position(pos), poids(u), rbfAssociate(indiceRBF) {};


    void InterpolationFunc::setPoids(VectorXd poids) {
        this->poids = poids;
    }

    void InterpolationFunc::addContrainte(int x, int y, int z) {
        this->position.push_back(glm::vec2(x, y));
        this->poids << z;
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

    void InterpolationFunc::drawFunc(int X, int Y, World world) {
        //Pseudo code :
        for(int i =0; i<X; i++) {
            for(int j=0; j<Y; j++) {
                int z = calculInterpolation(glm::vec2(i,j));
                for(int k=0; k<z; k++) {
                    world.extrude(glm::vec3(i, j, k));
                }
            }
        }
    }

}
//RBF UTILISATION_________________________________________________________________
