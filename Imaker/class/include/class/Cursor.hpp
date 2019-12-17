#pragma once

#include <glm/glm.hpp>
#include <vector>
#include "class/Cube.hpp"

#include "glimac/common.hpp"

using namespace glimac;
namespace Imaker{

  class Cursor : public Cube {
    public :
      Cursor();

      glm::vec3 getCursorPos();
      void updatePosX(int direction);
      void updatePosY(int direction);
      void updatePosZ(int direction);
      void drawCursor(glm::mat4 globalMVMatrix, GLint uMVPMatrixLoc, GLint uMVMatrixLoc, GLint uNormalMatrixLoc);


    private :

  };
}
