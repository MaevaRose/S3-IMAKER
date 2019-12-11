#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>

using namespace glimac;

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

        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}
