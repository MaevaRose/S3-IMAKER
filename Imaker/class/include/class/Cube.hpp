#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <string>

#include "glimac/common.hpp"

using namespace glimac;
namespace Imaker{

  struct cubeType {
    glm::vec3 color;
    std::string name;

    cubeType(){
    }

    cubeType(glm::vec3 colors, std::string typeName){
      color = colors;
      name = typeName;
    }

    bool operator==(const cubeType &type) const{
      return ( (color.x == type.color.x)
            && (color.y == type.color.y)
            && (color.z == type.color.z)
            && (name == type.name));
    }
  };

  class Cube {

    public :
      // constructeurs et destructeur
      Cube();
      Cube(glm::vec3 vecPosition);
      Cube(glm::vec3 vecPosition, bool visibility, cubeType cubetype);
      ~Cube();

      void drawCubeScaled(glm::mat4 globalMVMatrix, GLint uMVPMatrixLoc, GLint uMVMatrixLoc, GLint uNormalMatrixLoc, GLint cubeColorLoc, int width, int length, int height);
      void drawCube(glm::mat4 globalMVMatrix, GLint uMVPMatrixLoc, GLint uMVMatrixLoc, GLint uNormalMatrixLoc, GLint cubeColorLoc); // afficher un cube avec TrackBallCamera
      bool isVisible();
      void fillCube();
      void deleteCube();
      void editType(cubeType newType);
      void destroy();
      glm::vec3 getPos();
      cubeType returnCubeType();


    protected :
      GLuint m_vao;
      GLuint m_ibo;
      GLuint m_vbo;

      glm::vec3 position;
      cubeType type;
      bool visible;

  };
}
