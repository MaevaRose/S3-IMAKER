#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/TrackBallCamera.hpp>
#include <iostream>
#include <vector>
#include <class/Cursor.hpp>
#include <class/Interface.hpp>


using namespace glimac;
using namespace Imaker;


void destroyWorld(World &world, Cursor &cursor){
  cursor.destroy();
  for(int i = 0 ; i < world.width ; i++ ){
      for(int j = 0 ; j < world.length ; j++){
          for(int k = 0 ; k < world.height ; k++){
              world.allCubes[i][j][k].destroy();
          }
      }
  }
  world.destroy();
}

int main(int argc, char** argv) {

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

     //Pour le modèle de blinnPhong
     GLint uKd = glGetUniformLocation(program.getGLId(), "uKd");
     GLint uKs = glGetUniformLocation(program.getGLId(), "uKs");
     GLint uShininess = glGetUniformLocation(program.getGLId(), "uShininess");
     GLint uLightDir = glGetUniformLocation(program.getGLId(), "uLightDir");
     GLint uLightIntensity = glGetUniformLocation(program.getGLId(), "uLightIntensity");
     GLint uLightPos = glGetUniformLocation(program.getGLId(), "uLightPos");

     //empêcher que les triangles invisibles recouvrent ceux devant
     glEnable(GL_DEPTH_TEST);

     //variables matricielles
     glm::mat4 ProjMatrix, MVMatrix, NormalMatrix, globalMVMatrix;

     //calcul ProjMatrix
     ProjMatrix = glm::perspective(glm::radians(50.f), //angle vertical de vue
                                   1.8f, // ratio largeur/hauteur de la fenêtre
                                 0.1f, // near et
                               100.f); //far définissent une range de vision sur l'axe de la profondeur

     MVMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, -5));


     //calcul NormalMatrix avec NormalMatrix=(MV^−1)^T,
     NormalMatrix = glm::transpose(glm::inverse(MVMatrix));


    //Création currentFile.world
    //World world(25, 25, 25);
    //File currentFile("/home/maeva/Documents/PROJET_S3/S3-IMAKER/Imaker/assets/data/save1.imaker");
    File currentFile;    //déclaration du cube
    //Cube cube;
    //Cube cube2(glm::vec3(20, 20, 20));
    //std::vector<std::vector<std::vector<Cube>>> allCubes(5,std::vector<std::vector<Cube> >(5,std::vector <Cube>(5)));
    //currentFile.world.createScene();
    //currentFile.world.allCubeTypes.push_back(cubeType(glm::vec3(0,0,1), "Bleu (défaut)"));
    //currentFile.world.allCubeTypes.push_back(cubeType(glm::vec3(1,1,1), "Blanc (défaut)"));
    Cursor cursor;
    glm::vec3 cursorPos;

    /* Création de la camera */
    TrackBallCamera camera;
    //ZONE DE TEST DES FONCTIONS ////////////////////////////////////////////////////////
    Cube cubeTest(glm::vec3(0,0,0));
    //cubeTest.fillCube();

    //pour déplacer le curseur pas trop vite
    int count = 0;
    int vitesse = 100;

    ///////////////////////////////////////////////////////////////////////////////////////////

    // Application loop:
    bool done = false;
    while(!done) {

        // Event loop:
        SDL_Event e;

        while(interface.windowManager.pollEvent(e)) {
          ImGui_ImplSDL2_ProcessEvent(&e);
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }

        }

        cursorPos = cursor.getCursorPos();
        interface.startFrame();
        interface.MainMenuBar(currentFile);
        interface.browserFile(currentFile);
        interface.saveWindow();
        interface.saveAsWindow(currentFile);
        interface.overwriteWindow(currentFile);
        interface.createNewWorldWindow(currentFile);
        interface.selectionTypeCube(currentFile.world.allCubes[cursorPos.x][cursorPos.y][cursorPos.z], currentFile.world);
    //Pas de sdl event si on est sur une fenêtre ImGui
    interface.io = ImGui::GetIO();
    if(interface.io.WantCaptureMouse){
      ImGui::CaptureKeyboardFromApp(true);
    }
    else{
      ImGui::CaptureKeyboardFromApp(false);

      if( e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE))
      {
          done = true;
          break;
      }

      switch(e.type) {

         /* Touche clavier */
       case SDL_KEYDOWN:
         {
           float zoom = 0.1f;
           if (e.key.keysym.sym == SDLK_UP) {
             //std::cout << "Z or UP pressed" << std::endl;
             camera.moveFront(-zoom);
           }
           else if (e.key.keysym.sym == SDLK_DOWN) {
             //std::cout << "S or DOWN pressed" << std::endl;
             camera.moveFront(zoom);
           }

           //DEPLACEMENT CURSEUR
           else if(e.key.keysym.sym == SDLK_KP_6){
             count++;
             if(count == vitesse){
               cursor.updatePosX(1, currentFile.world.width);
               count = 0;
             }
           }
           else if(e.key.keysym.sym == SDLK_KP_4){
             count++;
             if(count == vitesse){
               cursor.updatePosX(-1, currentFile.world.width);
               count = 0;
             }
           }
           else if(e.key.keysym.sym == SDLK_KP_8){
             count++;
             if(count == vitesse){
               cursor.updatePosY(1, currentFile.world.length);
               count = 0;
             }
           }
           else if(e.key.keysym.sym == SDLK_KP_2){
             count++;
             if(count == vitesse){
               cursor.updatePosY(-1, currentFile.world.length);
               count = 0;
             }
           }
           else if(e.key.keysym.sym == SDLK_KP_9){
             count++;
             if(count == vitesse){
               cursor.updatePosZ(1, currentFile.world.height);
               count = 0;
             }
           }
           else if(e.key.keysym.sym == SDLK_KP_1){
             count++;
             if(count == vitesse){
               cursor.updatePosZ(-1, currentFile.world.height);
               count = 0;
             }
           }

         }
         break;

      case SDL_KEYUP:
        { count = 99;


          if(e.key.keysym.sym == SDLK_c){
           cursorPos = cursor.getCursorPos();
           currentFile.world.allCubes[cursorPos.x][cursorPos.y][cursorPos.z].fillCube();
           e.type = 0;
          }
          else if(e.key.keysym.sym == SDLK_v){
            cursorPos = cursor.getCursorPos();
            currentFile.world.allCubes[cursorPos.x][cursorPos.y][cursorPos.z].deleteCube();
            e.type = 0;
          }
          //else if(e.key.keysym.sym == SDLK_s) currentFile.saveFile("../testSauvegarde1.imaker");
          else if(e.key.keysym.sym == SDLK_e){
            cursorPos = cursor.getCursorPos();
            currentFile.world.extrude(cursorPos);
            //extrude(currentFile.world.allCubes[cursorPos.x][cursorPos.y][cursorPos.z], currentFile.world);
            e.type = 0;
          }
          else if(e.key.keysym.sym == SDLK_d){
            cursorPos = cursor.getCursorPos();
            currentFile.world.dig(cursorPos);
            //dig(currentFile.world.allCubes[cursorPos.x][cursorPos.y][cursorPos.z], currentFile.world);
            e.type = 0;
          }
        }
        break;

       case SDL_MOUSEMOTION :
         {
           float speed = 0.1f;

           // la scène tourne si le bouton gauche de la souris est enfoncé
           if (e.motion.state & SDL_BUTTON_LMASK)
            {
                if ( e.motion.xrel != 0 ) {
                  camera.rotateLeft( float(e.motion.xrel) * speed);
                  e.type = 0;
                }
                if ( e.motion.yrel != 0 ) {
                  camera.rotateUp( float(e.motion.yrel) * speed);
                  e.type = 0;
                }
            }

         }
         break;

       case SDL_MOUSEWHEEL : {
         float zoom = 1.f;
         if(e.wheel.y > 0) // scroll up
         {
            camera.moveFront(-zoom);
            e.type = 0;
          }
          else if(e.wheel.y < 0) // scroll down
          {
            camera.moveFront(zoom);
            e.type = 0;
          }
       }

       default:
           break;
     }
   }//interface hovered or not


        //std::cout<<interface.io.WantCaptureMouse<<std::endl;
        /*********************************
         * RENDERING CODE
         *********************************/
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        globalMVMatrix = camera.getViewMatrix(currentFile.world);

        glm::vec4 lightDir4 =  glm::vec4(1.0f, 1.0f, 1.0f, 0.0f);
        lightDir4 =  globalMVMatrix * lightDir4;
        glm::vec3 lightDir = glm::vec3(lightDir.x, lightDir.y, lightDir.z);

       glUniform3fv(uKd, 1, glm::value_ptr(glm::vec3(0.5)));
       glUniform3fv(uKs, 1, glm::value_ptr(glm::vec3(0.2)));
       glUniform1f(uShininess, 0.1);
       glUniform3fv(uLightDir, 1, glm::value_ptr(glm::vec3(0.5, 1.f, 0.8)));
       glUniform3fv(uLightIntensity, 1, glm::value_ptr(glm::vec3(5000.f)));
       glUniform3fv(uLightPos, 1, glm::value_ptr(glm::vec3(1.f)));




        glDepthRange(0, 0.01);



        cursor.drawCursor(globalMVMatrix, uMVPMatrixLoc, uMVMatrixLoc, uNormalMatrixLoc, cubeColorLoc);
        //cursor.returnPos();

        // reserve 99% of the back depth range for the 3D axis
        glDepthRange(0.01, 1.0);

        currentFile.world.drawScene(globalMVMatrix, uMVPMatrixLoc, uMVMatrixLoc, uNormalMatrixLoc, cubeColorLoc);
        currentFile.world.drawWorld(globalMVMatrix, uMVPMatrixLoc, uMVMatrixLoc, uNormalMatrixLoc, cubeColorLoc);
          // restore depth range
          glDepthRange(0, 1.0);

          interface.posCamera(camera);

          interface.render();
         //cube.drawCubeRotative(windowManager.getTime(), uMVPMatrixLoc, uMVMatrixLoc, uNormalMatrixLoc);

        // Update the display
        interface.windowManager.swapBuffers();
    }

    destroyWorld(currentFile.world, cursor);

    return EXIT_SUCCESS;
}
