#pragma once
#include <iostream>
#include <class/Cube.hpp>


namespace Imaker{
    class World : public Cube {

        public:

        //constructor
        World();
        World(int height, int width, int len);


        //methodes
        int getHeight();
        int getWidth();
        int getLength();

        void createScene();
        void drawScene(glm::mat4 globalMVMatrix, GLint uMVPMatrixLoc, GLint uMVMatrixLoc, GLint uNormalMatrixLoc, GLint cubeColorLoc);
        void drawWorld(glm::mat4 globalMVMatrix, GLint uMVPMatrixLoc, GLint uMVMatrixLoc, GLint uNormalMatrixLoc, GLint cubeColorLoc);
        void createNewCubeType(glm::vec3 color, char cubeName[32]);

        public :

        //attributs
        int height;
        int width;
        int length;
        int ground; //POURQUOI ?
        std::vector<std::vector<std::vector<Cube>>> allCubes;
        std::vector<cubeType> allCubeTypes;
    };

    //AUTRES METHODES
    void extrude(Cube cube, World world);
    void dig(Cube cube, World world);
}
