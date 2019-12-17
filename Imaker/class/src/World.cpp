#include <iostream>
#include <vector>
#include <../include/class/world.hpp>

namespace Imaker {


    World::World() : height(100), width(100), length(100),  ground(0), allCubes(5,std::vector<std::vector<Cube>>(5,std::vector <Cube>(5) ) ) {};
    World::World(int hei, int wid, int len) : height(hei), width(wid), length(len),  allCubes(5,std::vector<std::vector<Cube>>(5,std::vector <Cube>(5) ) ){};

    int World::getHeight() {
        return this -> height;
    }

    int World::getWidth() {
        return this -> width;
    }

    void World::createScene(){
        for(int i = 0 ; i < 5 ; i++ ){
            for(int j = 0 ; j < 5 ; j++){
                for(int k = 0 ; k < 5 ; k++){
                    Cube temp_cube(glm::vec3(i,j,k));
                    this->allCubes[i][j][k] = temp_cube;
                }
            }
        }
    }

    void World::drawScene(glm::mat4 globalMVMatrix, GLint uMVPMatrixLoc, GLint uMVMatrixLoc, GLint uNormalMatrixLoc){
        for(int i = 0 ; i < 5 ; i++ ){
            for(int j = 0 ; j < 5 ; j++){
                for(int k = 0 ; k < 5 ; k++){
                    if(this->allCubes[i][j][k].isVisible()){
                        this->allCubes[i][j][k].drawCube(globalMVMatrix, uMVPMatrixLoc, uMVMatrixLoc, uNormalMatrixLoc);
                    }
                }
            }
        }
    }

    void World::drawWorld(glm::mat4 globalMVMatrix, GLint uMVPMatrixLoc, GLint uMVMatrixLoc, GLint uNormalMatrixLoc) {



        //Wireframe mode on
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        //dessin
        drawCubeScaled(globalMVMatrix, uMVPMatrixLoc, uMVMatrixLoc, uNormalMatrixLoc, this->width, this->length, this->height);

        //WireframeM mode off
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        glBindVertexArray(0);
    }
}

