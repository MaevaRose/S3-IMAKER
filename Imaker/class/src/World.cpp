#include <iostream>
#include <vector>
#include <class/World.hpp>

namespace Imaker {


    World::World() : height(100), width(100), length(100),  ground(0), allCubes(100,std::vector<std::vector<Cube>>(100,std::vector <Cube>(100) ) ) {};
    World::World(int hei, int wid, int len) : height(hei), width(wid), length(len), ground(0),  allCubes(wid,std::vector<std::vector<Cube>>(len,std::vector <Cube>(hei) ) ) {};


    int World::getHeight() {
        return this -> height;
    }

    int World::getWidth() {
        return this -> width;
    }

    int World::getLength() {
        return this -> length;
    }

    void World::createScene(){
        type = cubeType(glm::vec3(1,1,1), "Blanc");
        for(int i = 0 ; i < this->width ; i++ ){
            for(int j = 0 ; j < this->length ; j++){
                for(int k=0; k<3; k++) {
                    Cube temp_cube(glm::vec3(i,j,k));
                    temp_cube.fillCube();
                    this->allCubes[i][j][k] = temp_cube;
                }
                for(int k = 3 ; k < this->height ; k++){
                    Cube temp_cube(glm::vec3(i,j,k));
                    this->allCubes[i][j][k] = temp_cube;
                }
            }
        }
    }

    void World::drawScene(glm::mat4 globalMVMatrix, GLint uMVPMatrixLoc, GLint uMVMatrixLoc, GLint uNormalMatrixLoc, GLint cubeColorLoc){
        for(int i = 0 ; i < this->width ; i++ ){
            for(int j = 0 ; j < this->length ; j++){
                for(int k = 0 ; k < this->height ; k++){
                    if(this->allCubes[i][j][k].isVisible()){
                        this->allCubes[i][j][k].drawCube(globalMVMatrix, uMVPMatrixLoc, uMVMatrixLoc, uNormalMatrixLoc, cubeColorLoc);
                    }
                }
            }
        }
    }

    void World::drawWorld(glm::mat4 globalMVMatrix, GLint uMVPMatrixLoc, GLint uMVMatrixLoc, GLint uNormalMatrixLoc, GLint cubeColorLoc) {

        //Wireframe mode on
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        //dessin
        drawCubeScaled(globalMVMatrix, uMVPMatrixLoc, uMVMatrixLoc, uNormalMatrixLoc, cubeColorLoc, this->width, this->length, this->height);

        //WireframeM mode off
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


    }



    void World::extrude(glm::vec3 pos) {
        if(!allCubes[pos.x][pos.y][pos.z].isVisible()) {
            return;
        }
        else {
            int z = pos.z;
            while(z < this->height) {
                if(!allCubes[pos.x][pos.y][z+1].isVisible()) {
                    allCubes[pos.x][pos.y][z+1].fillCube();
                    return;
                }
                else {
                    z++;
                }
            }
        }
    }


    void World::dig(glm::vec3 pos) {
        if(!allCubes[pos.x][pos.y][pos.z+1].isVisible()) {
            return;
        }
        else {
            int z = pos.z+1;
            if(z == this->height) {
                allCubes[pos.x][pos.y][z].deleteCube();
                return;
            }
            while(z < this->height-1) {
                if(!allCubes[pos.x][pos.y][z+1].isVisible()) {
                    allCubes[pos.x][pos.y][z].deleteCube();
                    return;
                }
                else {
                    z++;
                }
            }
        }
    }



    void World::createNewCubeType(glm::vec3 color, char cubeName[32]){
      std::string temp_value(cubeName);
      allCubeTypes.push_back(cubeType(color, temp_value));
    }
}
