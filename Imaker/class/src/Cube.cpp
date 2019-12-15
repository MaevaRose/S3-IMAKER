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
        glm::vec3(1, 1, 1), glm::vec3(-1, 1, 1), glm::vec3(-1, -1, 1), glm::vec3(1, -1, 1),
        // Right v0,v3,v4,v5
        glm::vec3(1, 1, 1), glm::vec3(1, -1, 1), glm::vec3(1, -1, -1), glm::vec3(1, 1, -1),
        // Top v0,v5,v6,v1
        glm::vec3(1, 1, 1), glm::vec3(1, 1, -1), glm::vec3(-1, 1, -1), glm::vec3(-1, 1, 1),
        // Left v1,v6,v7,v2
        glm::vec3(-1, 1, 1), glm::vec3(-1, 1, -1), glm::vec3(-1, -1, -1), glm::vec3(-1, -1, 1),
        // Bottom v7,v4,v3,v2
        glm::vec3(-1, -1, -1), glm::vec3(1, -1, -1), glm::vec3(1, -1, 1), glm::vec3(-1, -1, 1),
        // Back v4,v7,v6,v5
        glm::vec3(1, -1, -1), glm::vec3(-1, -1, -1), glm::vec3(-1, 1, -1), glm::vec3(1, 1, -1)
    };

    const glm::vec3 normals[] = {
        glm::vec3(0, 0, 1), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1), glm::vec3(0, 0, 1),
        glm::vec3(1, 0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0), glm::vec3(1, 0, 0),
        glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0),
        glm::vec3(-1, 0, 0), glm::vec3(-1, 0, 0), glm::vec3(-1, 0, 0), glm::vec3(-1, 0, 0),
        glm::vec3(0,-1, 0), glm::vec3(0,-1, 0), glm::vec3(0,-1, 0), glm::vec3(0,-1, 0),
        glm::vec3(0, 0,-1), glm::vec3(0, 0,-1), glm::vec3(0, 0,-1), glm::vec3(0, 0,-1)
    };

    const unsigned short indices[] = {
        0, 1, 2,   2, 3, 0,       // front
        4, 5, 6,   6, 7, 4,       // right
        8, 9, 10,  10,11,8,       // top
        12,13,14,  14,15,12,      // left
        16,17,18,  18,19,16,      // bottom
        20,21,22,  22,23,20		  // back
    };

    //calcul ProjMatrix
    glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), //angle vertical de vue
                                  1.f, // ratio largeur/hauteur de la fenêtre
                                0.1f, // near et
                              100.f); //far définissent une range de vision sur l'axe de la profondeur

    glm::mat4 MVMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, -5));


    //calcul NormalMatrix avec NormalMatrix=(MV^−1)^T,
    glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
}

namespace Imaker{

  Cube::Cube() :  m_vao(0), m_ibo(0) {
    /*********************************
     * VBO
     *********************************/

    GLuint vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

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

    glBindBuffer(GL_ARRAY_BUFFER, vbo); // on binde le vbo
    // Vertex input description

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE,
      3 * sizeof(float), 0);

    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE,
      3 * sizeof(float), 0);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    /*********************************
    * Uniforms
    *********************************/


  }

  Cube::~Cube() {

  }

  void Cube::drawCube(GLint uMVPMatrixLoc, GLint uMVMatrixLoc, GLint uNormalMatrixLoc){

    // glm::mat4 ProjMatrix = glm::perspective(glm::radians(70.f), //angle vertical de vue
    //                               1.f, // ratio largeur/hauteur de la fenêtre
    //                             0.1f, // near et
    //                           100.f); //far définissent une range de vision sur l'axe de la profondeur
    //
    // glm::mat4 MVMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, -5));
    //
    //
    // //calcul NormalMatrix avec NormalMatrix=(MV^−1)^T,
    // glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

    glUniformMatrix4fv(uMVMatrixLoc, 1, GL_FALSE, glm::value_ptr(cubeData::MVMatrix));
    glUniformMatrix4fv(uMVPMatrixLoc, 1, GL_FALSE, glm::value_ptr(cubeData::ProjMatrix * cubeData::MVMatrix));
    glUniformMatrix4fv(uNormalMatrixLoc, 1, GL_FALSE, glm::value_ptr(cubeData::NormalMatrix));

    glDrawElements(GL_TRIANGLES, sizeof(cubeData::indices), GL_UNSIGNED_SHORT, (void*) 0);
    //glDrawArrays(GL_TRIANGLES, 0, 12*3);

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
    //glDrawArrays(GL_TRIANGLES, 0, 12*3);

    glBindVertexArray(0);
  }

} //namespace
