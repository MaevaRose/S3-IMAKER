#include <iostream>
#include <../include/class/Cube.hpp>

class World {

    public:

    //constructor
    World();
    World(int height, int width, int len);

    //methodes
    int getHeight();
    int getWidth();
    int getLength();

    void drawConstrutionArea();

    protected:

    //attributs
    int height;
    int width;
    int length;
    int ground; //POURQUOI ?
    //std::vector<Cube> allCubes;  
};