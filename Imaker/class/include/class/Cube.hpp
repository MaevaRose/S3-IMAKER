#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "glimac/common.hpp"

using namespace glimac;
namespace Imaker{

  class Cube {
    public :
      Cube();
      Cube(glm::vec3 vecPosition);
      ~Cube();

      void drawCube(glm::mat4 globalMVMatrix, GLint uMVPMatrixLoc, GLint uMVMatrixLoc, GLint uNormalMatrixLoc); // afficher un cube avec TrackBallCamera
      void drawCubeScaled(glm::mat4 globalMVMatrix, GLint uMVPMatrixLoc, GLint uMVMatrixLoc, GLint uNormalMatrixLoc, int width, int length, int height);
      void drawCubeRotative(float time, GLint uMVPMatrixLoc, GLint uMVMatrixLoc, GLint uNormalMatrixLoc);
      bool isVisible();
      void fillCube();
      void deleteCube();
      void editColor();
      void returnPos();

    protected :
      GLuint m_vao;
      GLuint m_ibo;
      GLuint m_vbo;

      glm::vec3 position;
      glm::vec3 color;
      bool visible;

  };
}
