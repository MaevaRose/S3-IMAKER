#include <iostream>
#include <class/RBF.hpp>


using namespace Eigen;


namespace Imaker{
    //RADIAL FUNCTIONS _____________________________________________________________

    float rbfLineaire(const float dist, const float alpha) {                    // indice 1
        return alpha * dist;
    }

    float rbfMultiQuad(const float dist, const float alpha) {                   // indice 2
        return sqrt(1 + (alpha * dist) * (alpha * dist));
    }

    float rbfInverseQuad(const float dist, const float alpha) {                 // indice 3
        return 1/(1 + (alpha * dist) * (alpha * dist));
    }

    float rbfInverseMultiQuad(const float dist, const float alpha) {            // indice 4
        return 1/(sqrt(1 + (alpha * dist) * (alpha * dist)));
    }

    float rbfGauss(const float dist, const float alpha) {                       // indice 5
        return exp(-(alpha * dist) * (alpha * dist));
    }



    //INTERPOLATION FUNC CLASS_______________________________________________________

    InterpolationFunc::InterpolationFunc() : rbfAssociate(5), alpha(-1) {};
    InterpolationFunc::InterpolationFunc(std::vector<glm::vec2> pos, std::vector<double> u, int indiceRBF, float coeff) : position(pos), poids(u), rbfAssociate(indiceRBF), alpha(coeff) {};
    InterpolationFunc::~InterpolationFunc() {}

    void InterpolationFunc::setPoids(const std::vector<double> &poids) {
        this->poids = poids;
    }

    void InterpolationFunc::deleteContraintes(const int indice) {
      if ( this->position.size() > 0 && this->poids.size() > 0){
        this->position.erase(position.begin()+indice);
        this->poids.erase(poids.begin()+indice);
      }
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

    void InterpolationFunc::addContrainte(const int &x, const int &y, const int &z) {
        this->position.push_back(glm::vec2(x, y));
        this->poids.push_back(z);
    }


    MatrixXd InterpolationFunc::buildMatContrainte() const {
        int dim = this->poids.size();
        MatrixXd contraintes(dim, dim);
        for(int i=0; i<dim; i++) {
            for(int j=0; j<dim; j++) {
                contraintes(i, j) = RBF(this->position[i], this->position[j]);
            }
        }
        return contraintes;
    }

    void InterpolationFunc::calculW(const MatrixXd &contraintes) {
        int nbContraintes = this->poids.size();
        VectorXd eigenPoids;
        eigenPoids.resize(nbContraintes);
        for(int i=0; i<nbContraintes; i++) {
            eigenPoids(i)=this->poids[i];
        }
        ColPivHouseholderQR<Eigen::MatrixXd> dec(contraintes);
        this->w = dec.solve(eigenPoids);
    }


    float InterpolationFunc::calculInterpolation(const glm::vec2 &point) const {
        float somme = 0;
        for(int i=0; i<this->poids.size(); i++) {
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
                    for(int k=0; k<z && k<world.getHeight()-2; k++) {
                        world.extrude(glm::vec3(i, j, k));
                    }
                }
            }
        }
    }

}
