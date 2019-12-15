#pragma once

#include <glm/glm.hpp>
#include <vector>

#include "glimac/common.hpp"

using namespace glimac;
namespace Imaker{

  class Cube {
    public :
      Cube();
      ~Cube();

      void drawCube(GLint uMVPMatrixLoc, GLint uMVMatrixLoc, GLint uNormalMatrixLoc);
      glm::vec3 returnPos();
      bool isEmpty();
      void fillCube();
      void deleteCube();
      void editColor();
      bool empty;

    private :
      GLuint m_vao;
      GLuint m_ibo;
      // Shader m_shader;

      glm::vec3 position;
      glm::vec3 color;


  };
}
