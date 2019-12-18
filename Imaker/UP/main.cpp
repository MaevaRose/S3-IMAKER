#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/TrackBallCamera.hpp>
#include <iostream>
#include <vector>
#include <class/Cursor.hpp>
#include <class/Interface.hpp>
// #include <imgui/imgui_demo.cpp>
//#include <imgui/imgui_internal.h>

using namespace glimac;
using namespace Imaker;

void createScene(std::vector<std::vector<std::vector<Cube>>> &allCubes){
  for(int i = 0 ; i < 5 ; i++ ){
    for(int j = 0 ; j < 5 ; j++){
      for(int k = 0 ; k < 5 ; k++){
        Cube temp_cube(glm::vec3(i,j,k));
        allCubes[i][j][k] = temp_cube;
      }
    }
  }
}

void drawScene(std::vector<std::vector<std::vector<Cube>>> allCubes, glm::mat4 globalMVMatrix, GLint uMVPMatrixLoc, GLint uMVMatrixLoc, GLint uNormalMatrixLoc, GLint cubeColorLoc){
  for(int i = 0 ; i < 5 ; i++ ){
    for(int j = 0 ; j < 5 ; j++){
      for(int k = 0 ; k < 5 ; k++){
        if(allCubes[i][j][k].isVisible()){
          allCubes[i][j][k].drawCube(globalMVMatrix, uMVPMatrixLoc, uMVMatrixLoc, uNormalMatrixLoc, cubeColorLoc);
        }
      }
    }
  }
}


int main(int argc, char** argv) {
    // Initialize SDL and open a window
    // const int WINDOW_HEIGHT = 1200;
    // const int WINDOW_WIDTH = 1200;
    // SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "IMAKER - DURAND - ROSENBERG");
    //
    // // Initialize glew for OpenGL3+ support
    // GLenum glewInitError = glewInit();
    // if(GLEW_OK != glewInitError) {
    //     std::cerr << glewGetErrorString(glewInitError) << std::endl;
    //     return EXIT_FAILURE;
    // }
    //
    // std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    // std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    Interface interface;

    /*********************************
     * INITIALIZATION CODE
     *********************************/

     FilePath applicationPath(argv[0]);

     Program program = loadProgram(applicationPath.dirPath() + "shaders/" + argv[1],
                               applicationPath.dirPath() + "shaders/" + argv[2]);
     program.use();


     /*********************************
      * Pour les shaders
      *********************************/

     //récupérer les locations des variables uniformes des shaders
     GLint uMVPMatrixLoc = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
     GLint uMVMatrixLoc = glGetUniformLocation(program.getGLId(), "uMVMatrix");
     GLint uNormalMatrixLoc = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
     GLint cubeColorLoc = glGetUniformLocation(program.getGLId(), "cubeColor");

     //empêcher que les triangles invisibles recouvrent ceux devant
     glEnable(GL_DEPTH_TEST);

     //variables matricielles
     glm::mat4 ProjMatrix, MVMatrix, NormalMatrix, globalMVMatrix;

     //calcul ProjMatrix
     ProjMatrix = glm::perspective(glm::radians(70.f), //angle vertical de vue
                                   1.f, // ratio largeur/hauteur de la fenêtre
                                 0.1f, // near et
                               100.f); //far définissent une range de vision sur l'axe de la profondeur

     MVMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, -5));


     //calcul NormalMatrix avec NormalMatrix=(MV^−1)^T,
     NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

     /* Création de la camera */
     TrackBallCamera camera;
     //déclaration du cube
    //Cube cube;
     Cube cube2(glm::vec3(2, 0, 0));
     std::vector<std::vector<std::vector<Cube>>> allCubes(5,std::vector<std::vector<Cube> >(5,std::vector <Cube>(5)));
     createScene(allCubes);
     Cursor cursor;
     glm::vec3 cursorPos;



    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(interface.windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
            if( e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE))
            {
                done = true;
                break;
            }
        }

      switch(e.type) {

         /* Touche clavier */
       case SDL_KEYDOWN:
         {
           float zoom = 0.01f;
           if (e.key.keysym.sym == SDLK_z
               || e.key.keysym.sym == SDLK_UP) {
             //std::cout << "Z or UP pressed" << std::endl;
             camera.moveFront(zoom);
           }
           else if (e.key.keysym.sym == SDLK_s
                      || e.key.keysym.sym == SDLK_DOWN) {
             //std::cout << "S or DOWN pressed" << std::endl;
             camera.moveFront(-zoom);
           }

         }
         break;

      case SDL_KEYUP:
        { //cursorManager(e, cursor);
          if(e.key.keysym.sym == SDLK_c){
           cursorPos = cursor.getCursorPos();
           allCubes[cursorPos.x][cursorPos.y][cursorPos.z].fillCube();
           e.type = 0;
          }
          else if(e.key.keysym.sym == SDLK_v){
            cursorPos = cursor.getCursorPos();
            allCubes[cursorPos.x][cursorPos.y][cursorPos.z].deleteCube();
            e.type = 0;
          }
          else if(e.key.keysym.sym == SDLK_KP_6){
            cursor.updatePosX(1);
            e.type = 0;
          }
          else if(e.key.keysym.sym == SDLK_KP_4){
            cursor.updatePosX(-1);
            e.type = 0;
          }
          else if(e.key.keysym.sym == SDLK_KP_8){
            cursor.updatePosY(1);
            e.type = 0;
          }
          else if(e.key.keysym.sym == SDLK_KP_2){
            cursor.updatePosY(-1);
            e.type = 0;
          }
          else if(e.key.keysym.sym == SDLK_KP_9){
            cursor.updatePosZ(1);
            e.type = 0;
          }
          else if(e.key.keysym.sym == SDLK_KP_1){
            cursor.updatePosZ(-1);
            e.type = 0;
          }
          else if(e.key.keysym.sym == SDLK_y){
            cursorPos = cursor.getCursorPos();
            allCubes[cursorPos.x][cursorPos.y][cursorPos.z].editColor(1);
            e.type = 0;
          }
          else if(e.key.keysym.sym == SDLK_u){
            cursorPos = cursor.getCursorPos();
            allCubes[cursorPos.x][cursorPos.y][cursorPos.z].editColor(2);
            e.type = 0;
          }
          else if(e.key.keysym.sym == SDLK_i){
            cursorPos = cursor.getCursorPos();
            allCubes[cursorPos.x][cursorPos.y][cursorPos.z].editColor(3);
            e.type = 0;
          }
          else if(e.key.keysym.sym == SDLK_o){
            cursorPos = cursor.getCursorPos();
            allCubes[cursorPos.x][cursorPos.y][cursorPos.z].editColor(4);
            e.type = 0;
          }
        }
        break;

       case SDL_MOUSEMOTION:
         {
           float speed = 0.001f;
           //std::cout << "Mouse move: ";
           //std::cout << e.motion.xrel << " | " << e.motion.yrel << std::endl;
           if ( e.motion.xrel != 0 ) {
             camera.rotateUp( float(e.motion.xrel) * speed);
           }
           if ( e.motion.yrel != 0 ) {
             camera.rotateLeft( float(e.motion.yrel) * speed);
           }

         }
         break;

       default:
           break;
     }

        cursorPos = cursor.getCursorPos();
        /*********************************
         * RENDERING CODE
         *********************************/
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         globalMVMatrix = camera.getViewMatrix();

         interface.startFrame();


         // //pour afficher le curseur toujours au dessus
         // glClear(GL_DEPTH_BUFFER_BIT);


         glDepthRange(0, 0.01);

         cursor.drawCube(globalMVMatrix, uMVPMatrixLoc, uMVMatrixLoc, uNormalMatrixLoc, cubeColorLoc);
         //cursor.returnPos();

          // reserve 99% of the back depth range for the 3D axis
          glDepthRange(0.01, 1.0);

         drawScene(allCubes, globalMVMatrix, uMVPMatrixLoc, uMVMatrixLoc, uNormalMatrixLoc, cubeColorLoc);

          // restore depth range
          glDepthRange(0, 1.0);
          interface.selectionTypeCube(allCubes[cursorPos.x][cursorPos.y][cursorPos.z]);

          interface.render();
         //cube.drawCubeRotative(windowManager.getTime(), uMVPMatrixLoc, uMVMatrixLoc, uNormalMatrixLoc);

        // Update the display
        interface.windowManager.swapBuffers();
    }


    return EXIT_SUCCESS;
}
