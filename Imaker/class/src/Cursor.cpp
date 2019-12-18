#include "class/Cursor.hpp"



using namespace glimac;

namespace cursorData {

  //calcul ProjMatrix
  glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), //angle vertical de vue
                                1.f, // ratio largeur/hauteur de la fenêtre
                              0.1f, // near et
                            100.f); //far définissent une range de vision sur l'axe de la profondeur

  //calcul MVMatrix /!\ inutile si TrackBallCamera
  glm::mat4 MVMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, -5));


  //calcul NormalMatrix avec NormalMatrix=(MV^−1)^T,
  glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

}

namespace Imaker{


    Cursor::Cursor(){
      position = glm::vec3(2,2,2);
    }




    glm::vec3 Cursor::getCursorPos(){
      return position;
    }



    void Cursor::updatePosX(int direction, int width){
      position.x += direction;
      if(position.x < 0){
        position.x = 0;
      }
      if(position.x > width-1) {
        position.x --;
      }
    }



    void Cursor::updatePosY(int direction, int length){
      position.y += direction;
      if(position.y < 0){
        position.y = 0;
      }
      if(position.y > length-1) {
        position.y --;
      }
    }



    void Cursor::updatePosZ(int direction, int height){
      position.z += direction;
      if(position.z < 0){
        position.z = 0;
      }
      if(position.z > height-1) {
        position.z --;
      }
    }

  void Cursor::drawCursor(glm::mat4 globalMVMatrix, GLint uMVPMatrixLoc, GLint uMVMatrixLoc, GLint uNormalMatrixLoc, GLint cubeColorLoc) {
          //Wireframe mode on
          glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

          //dessin
          drawCube(globalMVMatrix, uMVPMatrixLoc, uMVMatrixLoc, uNormalMatrixLoc, cubeColorLoc);

          //WireframeM mode off
          glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  }


}
