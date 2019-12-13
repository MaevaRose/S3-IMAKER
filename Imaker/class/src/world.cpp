#include <iostream>
#include <vector>
#include <../include/class/world.hpp>


World::World() height(100), width(100), length(100),  ground(0) {};
World::World(int hei, int wid) : height(hei), width(wid), length(len) {};

int World::getHeight() {
    return this -> height;
}

int World::getWidth() {
    return this -> width;
}

void drawConstructionArea() {
    //récupérer la taille de la zone de construction 
    //Determiner les coordonnées exactes
    //

}