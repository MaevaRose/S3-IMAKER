#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "glimac/common.hpp"

using namespace glimac;
namespace Imaker{

  struct cubeType {
    glm::vec3 color;
    //string name;

    cubeType(){

    }

    cubeType(glm::vec3 colors){
      color = colors;
    }
  };

  class Cube {
    public :
      Cube();
      Cube(glm::vec3 vecPosition);
      ~Cube();

      void drawCubeScaled(glm::mat4 globalMVMatrix, GLint uMVPMatrixLoc, GLint uMVMatrixLoc, GLint uNormalMatrixLoc, GLint cubeColorLoc, int width, int length, int height);
      void drawCube(glm::mat4 globalMVMatrix, GLint uMVPMatrixLoc, GLint uMVMatrixLoc, GLint uNormalMatrixLoc, GLint cubeColorLoc); // afficher un cube avec TrackBallCamera
      void drawCubeRotative(float time, GLint uMVPMatrixLoc, GLint uMVMatrixLoc, GLint uNormalMatrixLoc);
      bool isVisible();
      void fillCube();
      void deleteCube();
      void editColor(int type);
      void editType(cubeType newType);
      void returnPos();
      void destroy();

    protected :
      GLuint m_vao;
      GLuint m_ibo;
      GLuint m_vbo;

      glm::vec3 position;
      glm::vec3 color;
      cubeType type;
      bool visible;

  };
}
