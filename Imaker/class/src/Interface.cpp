#include "class/Interface.hpp"



namespace Imaker{
  const int WINDOW_HEIGHT = 1200;
  const int WINDOW_WIDTH = 1200;

  Interface::Interface() : windowManager(glimac::SDLWindowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "IMAKER - DURAND - ROSENBERG")) {
    // Initialize glew for OpenGL3+ support

    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        exit(0);
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;


    SDL_GL_MakeCurrent(windowManager.window, windowManager.openglContext);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    //IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui_ImplSDL2_InitForOpenGL(windowManager.window, windowManager.openglContext);
    ImGui_ImplOpenGL3_Init("#version 130");

  }


  // Interface::~Interface{
  //     ImGui_ImplOpenGL3_Shutdown();
  //     ImGui_ImplSDL2_Shutdown();
  //     ImGui::DestroyContext();
  //
  //     SDL_GL_DeleteContext(windowManager.openglContext);
  //     SDL_DestroyWindow(windowManager.window);
  //     SDL_Quit();
  //   }

  void Interface::startFrame(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(windowManager.window);
    ImGui::NewFrame();

    ImGui::ShowDemoWindow();
  }

  void Interface::render(){
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }

} //namespace Imaker
