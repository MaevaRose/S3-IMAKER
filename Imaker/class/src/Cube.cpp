#include "class/Cube.hpp"
#include <iostream>

using namespace glimac;

namespace cubeData {
    //    v6----- v5
    //   /|      /|
    //  v1------v0|
    //  | |     | |
    //  | |v7---|-|v4
    //  |/      |/
    //  v2------v3
    const glm::vec3 positions[] = {
        // Front v0,v1,v2,v3
        glm::vec3(2, 2, 2), glm::vec3(0, 2, 2), glm::vec3(0, 0, 2), glm::vec3(2, 0, 2),
        // Right v0,v3,v4,v5
        glm::vec3(2, 2, 2), glm::vec3(2, 0, 2), glm::vec3(2, 0, 0), glm::vec3(2, 2, 0),
        // Top v0,v5,v6,v1
        glm::vec3(2, 2, 2), glm::vec3(2, 2, 0), glm::vec3(0, 2, 0), glm::vec3(0, 2, 2),
        // Left v2,v6,v7,v2
        glm::vec3(0, 2, 2), glm::vec3(0, 2, 0), glm::vec3(0, 0, 0), glm::vec3(0, 0, 2),
        // Bottom v7,v4,v3,v2
        glm::vec3(0, 0, 0), glm::vec3(2, 0, 0), glm::vec3(2, 0, 2), glm::vec3(0, 0, 2),
        // Back v4,v7,v6,v5
        glm::vec3(2, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 2, 0), glm::vec3(2, 2, 0)
    };

    // const glm::vec3 normals[] = {
    //     glm::vec3(0, 0, 1), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1),
    //     glm::vec3(1, 0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0),
    //     glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0),
    //     glm::vec3(-1, 0, 0), glm::vec3(-1, 0, 0), glm::vec3(-1, 0, 0), glm::vec3(-1, 0, 0),
    //     glm::vec3(0,-1, 0), glm::vec3(0,-1, 0), glm::vec3(0,-1, 0), glm::vec3(0,-1, 0),
    //     glm::vec3(0, 0,-1), glm::vec3(0, 0,-1), glm::vec3(0, 0,-1), glm::vec3(0, 0,-1)
    // };

    const unsigned short indices[] = {
        0, 1, 2,   2, 3, 0,       // front
        4, 5, 6,   6, 7, 4,       // right
        8, 9, 10,  10,11,8,       // top
        12,13,14,  14,15,12,      // left
        16,17,18,  18,19,16,      // bottom
        20,21,22,  22,23,20		  // back
    };

    const glm::vec3 rubiks[] = {
        glm::vec3(0, 0, 1), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1),
        glm::vec3(1, 0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0),
        glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0),
        glm::vec3(1, 1, 0), glm::vec3(1, 1, 0), glm::vec3(1, 1, 0), glm::vec3(1, 1, 0),
        glm::vec3(0,1, 1), glm::vec3(0,1, 1), glm::vec3(0,1, 1), glm::vec3(0,1, 1),
        glm::vec3(1, 0,1), glm::vec3(1, 0,1), glm::vec3(1, 0,1), glm::vec3(1, 0,1)
    };


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

  Cube::Cube() : visible(false), color(glm::vec3(0,1,1)), type(glm::vec3(0,1,1)) {

    /*********************************
     * VBO
     *********************************/

    GLuint m_vbo;
    glGenBuffers(1, &m_vbo);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeData::positions), cubeData::positions, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeData::rubiks), cubeData::rubiks, GL_STATIC_DRAW);



    /*********************************
     * IBO
     *********************************/
     //GLuint m_ibo;
     glGenBuffers(1, &m_ibo);

     //binder du GL_ELEMENT_ARRAY_BUFFER réservé pour les ibo
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeData::indices), cubeData::indices, GL_STATIC_DRAW);

     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    /*********************************
    * VAO
    *********************************/
    //GLuint vao;

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_COLOR = 2;

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo); // on binde le m_vbo
    // Vertex input description

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE,
      3 * sizeof(float), 0);

    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE,
      3 * sizeof(float), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);


    //couleurs
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE,
      3 * sizeof(float),  0);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



  }


  Cube::Cube(glm::vec3 vecPosition) :  m_vao(0), m_ibo(0), visible(false), position(vecPosition), color(glm::vec3(0,0,1)), type(glm::vec3(0,0,1)) {
    /*********************************
     * VBO
     *********************************/

    GLuint m_vbo;
    glGenBuffers(1, &m_vbo);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeData::positions), cubeData::positions, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);



    /*********************************
     * IBO
     *********************************/
     //GLuint m_ibo;
     glGenBuffers(1, &m_ibo);

     //binder du GL_ELEMENT_ARRAY_BUFFER réservé pour les ibo
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeData::indices), cubeData::indices, GL_STATIC_DRAW);

     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    /*********************************
    * VAO
    *********************************/
    //GLuint vao;

    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;


    glBindBuffer(GL_ARRAY_BUFFER, m_vbo); // on binde le m_vbo
    // Vertex input description

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE,
      3 * sizeof(float), 0);

    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE,
      3 * sizeof(float), 0);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



  }





  Cube::~Cube() {

  }

  void Cube::destroy(){
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
  }



  void Cube::drawCube(glm::mat4 globalMVMatrix, GLint uMVPMatrixLoc, GLint uMVMatrixLoc, GLint uNormalMatrixLoc, GLint cubeColorLoc){
    glBindVertexArray(m_vao);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glm::mat4 cubeMVMatrix = glm::translate(globalMVMatrix, position * glm::vec3(2,2,2)); // position x2 pour éviter le chevauchement des cubes

    glUniformMatrix4fv(uMVMatrixLoc, 1, GL_FALSE, glm::value_ptr(cubeMVMatrix));
    glUniformMatrix4fv(uMVPMatrixLoc, 1, GL_FALSE, glm::value_ptr(cubeData::ProjMatrix * cubeMVMatrix));
    glUniformMatrix4fv(uNormalMatrixLoc, 1, GL_FALSE, glm::value_ptr(cubeData::NormalMatrix));
    glUniform3fv(cubeColorLoc, 1, glm::value_ptr(type.color));

    glDrawElements(GL_TRIANGLES, sizeof(cubeData::indices), GL_UNSIGNED_SHORT, (void*) 0);


    glBindVertexArray(0);

  }

  void Cube::drawCubeScaled(glm::mat4 globalMVMatrix, GLint uMVPMatrixLoc, GLint uMVMatrixLoc, GLint uNormalMatrixLoc, GLint cubeColorLoc, int width, int length, int height){
    glBindVertexArray(m_vao);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

    glm::mat4 cubeMVMatrix = glm::scale(globalMVMatrix, glm::vec3(width, length, height));

    glUniformMatrix4fv(uMVMatrixLoc, 1, GL_FALSE, glm::value_ptr(cubeMVMatrix));
    glUniformMatrix4fv(uMVPMatrixLoc, 1, GL_FALSE, glm::value_ptr(cubeData::ProjMatrix * cubeMVMatrix));
    glUniformMatrix4fv(uNormalMatrixLoc, 1, GL_FALSE, glm::value_ptr(cubeData::NormalMatrix));
    glUniform3fv(cubeColorLoc, 1, glm::value_ptr(type.color));

    glDrawElements(GL_TRIANGLES, sizeof(cubeData::indices), GL_UNSIGNED_SHORT, (void*) 0);


    glBindVertexArray(0);
}







  void Cube::drawCubeRotative(float time, GLint uMVPMatrixLoc, GLint uMVMatrixLoc, GLint uNormalMatrixLoc){
    glm::mat4 MVMatrix = glm::rotate(cubeData::MVMatrix, time, glm::vec3(0.f, 1.f, 0.f));

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

    glUniformMatrix4fv(uMVMatrixLoc, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(uMVPMatrixLoc, 1, GL_FALSE, glm::value_ptr(cubeData::ProjMatrix * MVMatrix));
    glUniformMatrix4fv(uNormalMatrixLoc, 1, GL_FALSE, glm::value_ptr(cubeData::NormalMatrix));


    glDrawElements(GL_TRIANGLES, sizeof(cubeData::indices), GL_UNSIGNED_SHORT, (void*) 0);

    glBindVertexArray(0);
  }



  bool Cube::isVisible(){
    return visible;
  }



  void Cube::fillCube(){
    if(!visible){
      visible = true;
    }
    else std::cout << "Un cube existe déjà à cet emplacement" << std::endl;
  }


  void Cube::deleteCube(){
    if (visible){
      visible = false;
      //glDrawElements(GL_TRIANGLES, 0, GL_UNSIGNED_SHORT, (void*) 0);
    }
    else std::cout << "Aucun cube à supprimer" << std::endl;
  }

  void Cube::returnPos() {
    std::cout << "cube créé à la position " << position << std::endl;
  }

  void Cube::editColor(int type) {
    switch (type) {
      case 0: color = glm::vec3(1,0,0);
        break;
      case 1: color = glm::vec3(0,1,0);
        break;
      case 2: color = glm::vec3(0,0,1);
        break;
      case 3: color = glm::vec3(0,1,1);
        break;
      default : ;
        break;
    }
  }

  void Cube::editType(cubeType newType){
      type = newType;
  }

} //namespace
