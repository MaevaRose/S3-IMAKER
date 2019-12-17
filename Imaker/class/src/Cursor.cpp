#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include "class/Cursor.hpp"

#include "glimac/common.hpp"

using namespace glimac;

namespace cursorData {
  const glm::vec3 cursorColor(1,0,0);

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



    void Cursor::updatePosX(int direction){
      std::cout<<"updatePosX"<<std::endl;
      position.x += direction;
      if(position.x < 0){
        position.x = 0;
      }
    }



    void Cursor::updatePosY(int direction){
      position.y += direction;
      if(position.y < 0){
        position.y = 0;
      }
    }



    void Cursor::updatePosZ(int direction){
      position.z += direction;
      if(position.z < 0){
        position.z = 0;
      }
    }




}
