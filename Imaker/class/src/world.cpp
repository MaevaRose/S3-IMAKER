#include <iostream>
#include <vector>
#include <../include/class/world.hpp>

namespace Imaker {

    World::World() : height(100), width(100), length(100),  ground(0) {};
    World::World(int hei, int wid, int len) : height(hei), width(wid), length(len) {};

    int World::getHeight() {
        return this -> height;
    }

    int World::getWidth() {
        return this -> width;
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

