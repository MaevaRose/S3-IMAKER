#pragma once

#include <iostream>
#include <vector>
#include <glimac/glm.hpp>

class InterpolationFunc {
    public :

    //constructor
    InterpolationFunc();
    InterpolationFunc(std::vector<glm::vec3> p, std::vector<float> u, int indiceRBF);

    //Methodes
    void calculW();
    float calculInterpolation(int posX, int posY);
    

    private : 

    //attributs
    std::vector<std::vector<float>> P;
    std::vector<float> U;
    int rbfAssociate;
    std::vector<float> w;
};

void distance(float Xa, float Xb, float Ya, float Yb);