#include <iostream>
#include <../include/class/cube.h>

class World {

    public:

    //constructor
    World();
    World(int height, int width);

    //methodes
    int getHeight();
    int getWidth();
    int get 

    void drawConstrutionArea();

    protected:

    //attributs
    int height;
    int width;
    int ground; //POURQUOI ?
    std::vector<Cube> allCubes;  
}