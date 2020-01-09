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

      inline bool isVisible() const {return visible; }
      inline void editType(const cubeType &newType) {type = newType; }
      inline glm::vec3 getPos() const {return position; };
      inline cubeType returnCubeType() const {return type; };


      void destroy();
      void drawCube(const glm::mat4 &globalMVMatrix, const GLint &uMVPMatrixLoc, const GLint &uMVMatrixLoc, const GLint &uNormalMatrixLoc, const GLint &cubeColorLoc); // afficher un cube avec TrackBallCamera
      void drawCubeScaled(const glm::mat4 &globalMVMatrix, const GLint &uMVPMatrixLoc, const GLint &uMVMatrixLoc, const GLint &uNormalMatrixLoc, const GLint &cubeColorLoc, const int width, const int length, const int height);
      void fillCube();
      void deleteCube();


    protected :
      GLuint m_vao;
      GLuint m_ibo;
      GLuint m_vbo;

      glm::vec3 position;
      cubeType type;
      bool visible;

  };
}
