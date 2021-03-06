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

  const float normals[] = {
		// Front face
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
    0.0f,  1.0f,  0.0f,
		// Back face
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,
    0.0f,  0.0f, -1.0f,
		// Top face
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
    -1.0f,  0.0f,  0.0f,
		// Bot face
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
    1.0f,  0.0f,  0.0f,
		// Left face
    0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  1.0f,
    0.0f,  0.0f,  1.0f,

		// Right face
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
    0.0f, -1.0f,  0.0f,
	};

  const unsigned short indices[] = {
    0, 1, 2,   2, 3, 0,       // front
    4, 5, 6,   6, 7, 4,       // right
    8, 9, 10,  10,11,8,       // top
    12,13,14,  14,15,12,      // left
    16,17,18,  18,19,16,      // bottom
    20,21,22,  22,23,20		    // back
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
                                          1.f,                // ratio largeur/hauteur de la fenêtre
                                          0.1f,               // near et
                                          100.f);             //far définissent une range de vision sur l'axe de la profondeur

  //calcul MVMatrix /!\ inutile si TrackBallCamera
  glm::mat4 MVMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, -5));


  //calcul NormalMatrix avec NormalMatrix=(MV^−1)^T,
  glm::mat4 NormalMatrix = glm::transpose(glm::inverse(MVMatrix));
}




namespace Imaker{

  //constructeur 1
  Cube::Cube() : visible(false), type(glm::vec3(1,1,1), "Blanc") {

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

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);


    //couleurs
    glEnableVertexAttribArray(VERTEX_ATTR_COLOR);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),  0);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
  }



  //constructeur 2
  Cube::Cube(glm::vec3 vecPosition) :  m_vao(0), m_ibo(0), visible(false), position(vecPosition), type(glm::vec3(0,0,1), "Bleu") {
  
    /*********************************
   * VBO
   *********************************/

    GLuint m_vbo;
    glGenBuffers(1, &m_vbo);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeData::positions), cubeData::positions, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint normalsBuffer;
    glGenBuffers(1, &normalsBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeData::normals), cubeData::normals, GL_STATIC_DRAW);

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

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo); // on binde le m_vbo
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    glBindVertexArray(0);
  }


  //constructeur 3
  Cube::Cube(glm::vec3 vecPosition, bool visibility, cubeType cubetype) : m_vao(0), m_ibo(0), visible(visibility), position(vecPosition), type(cubetype){
    /*********************************
   * VBO
   *********************************/

    GLuint m_vbo;
    glGenBuffers(1, &m_vbo);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeData::positions), cubeData::positions, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint normalsBuffer;
    glGenBuffers(1, &normalsBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeData::normals), cubeData::normals, GL_STATIC_DRAW);


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

    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo); // on binde le m_vbo
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
  }



  //destructeur
  Cube::~Cube() {
  }


  //Méthodes
  void Cube::destroy(){
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ibo);
    glDeleteVertexArrays(1, &m_vao);
  }


  void Cube::drawCube(const glm::mat4 &globalMVMatrix, const GLint &uMVPMatrixLoc, const GLint &uMVMatrixLoc, const GLint &uNormalMatrixLoc, const GLint &cubeColorLoc){
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



  void Cube::drawCubeScaled(const glm::mat4 &globalMVMatrix, const GLint &uMVPMatrixLoc, const GLint &uMVMatrixLoc, const GLint &uNormalMatrixLoc, const GLint &cubeColorLoc, const int width, const int length, const int height){
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


  void Cube::fillCube() {
    if(!visible){
      visible = true;
    }
  }


  void Cube::deleteCube(){
    if (visible){
      visible = false;
    }
  }

} //namespace
