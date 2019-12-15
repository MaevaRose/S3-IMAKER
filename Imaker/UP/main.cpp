#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <iostream>
#include <class/Cube.hpp>

using namespace glimac;
using namespace Imaker;

int main(int argc, char** argv) {
    // Initialize SDL and open a window
    const int WINDOW_HEIGHT = 1200;
    const int WINDOW_WIDTH = 1200;
    SDLWindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "IMAKER - DURAND - ROSENBERG");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

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

     //empêcher que les triangles invisibles recouvrent ceux devant
     glEnable(GL_DEPTH_TEST);

     //variables matricielles
     glm::mat4 ProjMatrix;
     glm::mat4 MVMatrix;
     glm::mat4 NormalMatrix;

     //calcul ProjMatrix
     ProjMatrix = glm::perspective(glm::radians(70.f), //angle vertical de vue
                                   1.f, // ratio largeur/hauteur de la fenêtre
                                 0.1f, // near et
                               100.f); //far définissent une range de vision sur l'axe de la profondeur

     MVMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, -5));


     //calcul NormalMatrix avec NormalMatrix=(MV^−1)^T,
     NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

     //déclaration du cube
     Cube cube;

    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
            if( e.type == SDL_KEYDOWN && (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE))
            {
                done = true;
                break;
            }
        }


        /*********************************
         * RENDERING CODE
         *********************************/
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

         //bool lol = cube->isEmpty();
         cube.drawCube(uMVPMatrixLoc, uMVMatrixLoc, uNormalMatrixLoc);

        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}
