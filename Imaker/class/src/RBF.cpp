#include <iostream>
#include <class/RBF.hpp>


using namespace Eigen;


namespace Imaker{
    //RADIAL FUNCTIONS _____________________________________________________________

    float rbfLineaire(float dist, float alpha) {                    // indice 1
        return alpha * dist;
    }

    float rbfMultiQuad(float dist, float alpha) {                   // indice 2
        return sqrt(1 + (alpha * dist) * (alpha * dist));
    }

    float rbfInverseQuad(float dist, float alpha) {                 // indice 3
        return 1/(1 + (alpha * dist) * (alpha * dist));
    }

    float rbfInverseMultiQuad(float dist, float alpha) {            // indice 4
        return 1/(sqrt(1 + (alpha * dist) * (alpha * dist)));
    }

    float rbfGauss(float dist, float alpha) {                       // indice 5
        return exp(-(alpha * dist) * (alpha * dist));
    }



    //INTERPOLATION FUNC CLASS_______________________________________________________

    InterpolationFunc::InterpolationFunc() : rbfAssociate(5), alpha(-1) {};
    InterpolationFunc::InterpolationFunc(std::vector<glm::vec2> pos, std::vector<double> u, int indiceRBF, float coeff) : position(pos), poids(u), rbfAssociate(indiceRBF), alpha(coeff) {};


    void InterpolationFunc::setPoids(std::vector<double> poids) {
        this->poids = poids;
    }

    void InterpolationFunc::deleteContraintes(const int indice) {
        this->position.erase(position.begin()+indice);
        this->poids.erase(poids.begin()+indice);
    }

    void InterpolationFunc::setIndice(const int indiceRBF) {
      this->rbfAssociate = indiceRBF;
    }

    void InterpolationFunc::setAlpha(const float coeff) {
      this->alpha = coeff;
    }

    std::vector<double> InterpolationFunc::returnContraintes() const {
      return this->poids;
    }

    void InterpolationFunc::addContrainte(int x, int y, int z) {
        this->position.push_back(glm::vec2(x, y));
        this->poids.push_back(z);
    }

    // template<typename T>
    // float InterpolationFunc::RBF(const T &i, const T &j) {
    //     float dist = glm::length(this->position[i] - this->position[j]);
    //     switch(this->rbfAssociate) {
    //         case 1:
    //             return rbfLineaire(dist, this->alpha);
    //         break;

    //         case 2:
    //             return rbfMultiQuad(dist, this->alpha);
    //         break;

    //         case 3:
    //             return rbfInverseQuad(dist, this->alpha);
    //         break;

    //         case 4:
    //             return rbfInverseMultiQuad(dist, this->alpha);
    //         break;

    //         case 5:
    //             return rbfGauss(dist, this->alpha);
    //         break;

    //         default :
    //         break;

    //     }
    // }

    MatrixXd InterpolationFunc::buildMatContrainte() {
        int dim = this->poids.size();
        MatrixXd contraintes(dim, dim);
        for(int i=0; i<dim; i++) {
            for(int j=0; j<dim; j++) {
                contraintes(i, j) = RBF(this->position[i], this->position[j]);
            }
        }
        return contraintes;
    }

    void InterpolationFunc::calculW(MatrixXd contraintes) {
        int nbContraintes = this->poids.size();
        VectorXd eigenPoids;
        eigenPoids.resize(nbContraintes);
        for(int i=0; i<nbContraintes; i++) {
            eigenPoids(i)=this->poids[i];
        }
        ColPivHouseholderQR<Eigen::MatrixXd> dec(contraintes);
        this->w = dec.solve(eigenPoids);
    }


    float InterpolationFunc::calculInterpolation(glm::vec2 point) {
        float somme = 0;
        for(int i=0; i<this->poids.size(); i++) {
            //float rbf = RBF()
            somme += this->w[i] * RBF(point, this->position[i]);
        }
        return somme;
    }


    void InterpolationFunc::drawFunc(World &world) {
        int X = world.getLength();
        int Y = world.getWidth();
        for(int i =0; i<X; i++) {
            for(int j=0; j<Y; j++) {
                float z = calculInterpolation(glm::vec2(i,j));
                if(z>0) {
                    for(int k=0; k<z && k<23; k++) {
                        world.extrude(glm::vec3(i, j, k));
                    }
                }
                // else {
                //     while(world.allCubes[i][j][0].isVisible()){
                //         world.dig(glm::vec3(i,j,0));
                //     }
                // }
            }
        }
    }

}
