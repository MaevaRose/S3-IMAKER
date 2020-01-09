#pragma once
#include <iostream>
#include <class/Cube.hpp>


namespace Imaker{
    class World : public Cube {

        public:

        //constructor
        World();
        World(const int height, const int width, const int len);


        //methodes
        inline int getHeight() const {return height; }
        inline int getWidth() const {return width; };
        inline int getLength() const {return length; };
        inline std::vector<std::vector<std::vector<Cube>>> getAllCubes() const {return allCubes; }
        inline std::vector<cubeType> getAllCubeTypes() const {return allCubeTypes; }

        void createScene();
        void drawScene(const glm::mat4 &globalMVMatrix, const GLint &uMVPMatrixLoc, const GLint &uMVMatrixLoc, const GLint &uNormalMatrixLoc, const GLint &cubeColorLoc);
        void drawWorld(const glm::mat4 &globalMVMatrix, const GLint &uMVPMatrixLoc, const GLint &uMVMatrixLoc, const GLint &uNormalMatrixLoc, const GLint &cubeColorLoc);
        void createNewCubeType(const glm::vec3 &color, char cubeName[32]);
        void extrude(const glm::vec3 &pos);
        void dig(const glm::vec3 &pos);
        void reset();

        //attributs
        private :
            int height;
            int width;
            int length;

            std::vector<std::vector<std::vector<Cube>>> allCubes;
            std::vector<cubeType> allCubeTypes;
    };

}
