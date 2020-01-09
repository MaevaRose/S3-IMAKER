#include <iostream>
#include <vector>
#include <class/World.hpp>

namespace Imaker {


    World::World() : height(100), width(100), length(100), allCubes(100,std::vector<std::vector<Cube>>(100,std::vector <Cube>(100) ) ) {};
    World::World(const int hei, const int wid, const int len) : height(hei), width(wid), length(len), allCubes(wid,std::vector<std::vector<Cube>>(len,std::vector <Cube>(hei) ) ) {};
    World::~World() {}

    void World::reset(){
      for(int i = 0 ; i < this->width ; i++ ){
          for(int j = 0 ; j < this->length ; j++){
            for(int k=0; k<3; k++) {
                this->allCubes[i][j][k].fillCube();
            }
            for(int k = 3 ; k < this->height ; k++){
                this->allCubes[i][j][k].deleteCube();
            }
          }
      }
    }

    //construction de tous les cubes à partir de la taille donné au world
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

    void World::drawScene(const glm::mat4 &globalMVMatrix, const GLint &uMVPMatrixLoc, const GLint &uMVMatrixLoc, const GLint &uNormalMatrixLoc, const GLint &cubeColorLoc) {
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

    void World::drawWorld(const glm::mat4 &globalMVMatrix, const GLint &uMVPMatrixLoc, const GLint &uMVMatrixLoc, const GLint &uNormalMatrixLoc, const GLint &cubeColorLoc) {

        //Wireframe mode on
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        //dessin
        drawCubeScaled(globalMVMatrix, uMVPMatrixLoc, uMVMatrixLoc, uNormalMatrixLoc, cubeColorLoc, this->width, this->length, this->height);

        //WireframeM mode off
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }



    void World::extrude(const glm::vec3 &pos) {
        if(!allCubes[pos.x][pos.y][pos.z].isVisible()) {
            return;
        }
        else {
            int z = pos.z;
            while(z < this->height-1) {
                if(!allCubes[pos.x][pos.y][z+1].isVisible()) {
                    allCubes[pos.x][pos.y][z+1].fillCube();
                    allCubes[pos.x][pos.y][z+1].editType(allCubes[pos.x][pos.y][pos.z].returnCubeType());
                    return;
                }
                else {
                    z++;
                }
            }
        }
    }


    void World::dig(const glm::vec3 &pos) {
        if(!allCubes[pos.x][pos.y][pos.z+1].isVisible()) {
            return;
        }
        else {
            int z = pos.z+1;
            if(z == this->height) {
                allCubes[pos.x][pos.y][z].deleteCube();
                return;
            }
            while(z < this->height) {
                if(!allCubes[pos.x][pos.y][z+1].isVisible()) {
                    allCubes[pos.x][pos.y][z].deleteCube();
                    allCubes[pos.x][pos.y][z].editType(allCubes[pos.x][pos.y][pos.z].returnCubeType());
                    return;
                }
                else {
                    z++;
                }
            }
        }
    }



    void World::createNewCubeType(const glm::vec3 &color, char cubeName[32]){
      std::string temp_value(cubeName);
      allCubeTypes.push_back(cubeType(color, temp_value));
    }
}
