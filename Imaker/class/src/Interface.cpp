#include "class/Interface.hpp"



namespace Imaker{
  const int WINDOW_HEIGHT = 1000;
  const int WINDOW_WIDTH = 1000;

  Interface::Interface() : typeCube(0), windowManager(glimac::SDLWindowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "IMAKER - DURAND - ROSENBERG")) {
    // Initialize glew for OpenGL3+ support

    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        exit(0);
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    glMatrixMode(GL_PROJECTION);
    gluPerspective(45.f,1.f,0.1f,200.f);

    SDL_GL_MakeCurrent(windowManager.window, windowManager.openglContext);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = ImGui::GetIO(); (void)io;

    ImGui_ImplSDL2_InitForOpenGL(windowManager.window, windowManager.openglContext);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

  }


  Interface::~Interface(){
      ImGui_ImplOpenGL3_Shutdown();
      ImGui_ImplSDL2_Shutdown();
      ImGui::DestroyContext();

      SDL_GL_DeleteContext(windowManager.openglContext);
      SDL_DestroyWindow(windowManager.window);
      SDL_Quit();
    }

  void Interface::startFrame(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(windowManager.window);
    ImGui::NewFrame();

    ImGui::ShowDemoWindow();
  }

  // void Interface::selectionTypeCube(Cube &cube){
  //   ImGui::Begin("Cube Type");
  //   //ImGui::Button("Sélectionner Type!");
  //   if (ImGui::TreeNode("Selection Type")){
  //     for (int n = 0; n < 5; n++)
  //     {
  //         char buf[32];
  //         sprintf(buf, "Type %d", n);
  //         if (ImGui::Selectable(buf, typeCube == n)){
  //           typeCube = n;
  //           cube.editColor(typeCube);
  //         }
  //     }
  //     ImGui::TreePop();
  //   }
  //   ImGui::End();
  // }

  void Interface::selectionTypeCube(Cube &cube, World world){
    ImGui::Begin("Cube Type");
    //ImGui::Button("Sélectionner Type!");
    if (ImGui::TreeNode("Selection Type")){
      for (int n = 0; n < world.allCubeTypes.size(); n++)
      {
          char buf[32];
          sprintf(buf, "Type %d", n);
          if (ImGui::Selectable(buf, typeCube == n)){
            cube.editType(world.allCubeTypes[n]);
          }
      }
      ImGui::TreePop();
    }
    ImGui::End();
  }

  void Interface::posCamera(TrackBallCamera &camera){
    ImGui::Begin("Camera");
    ImGui::Text("m_fAngleX: %f", camera.m_fAngleX);
    ImGui::Text("m_fAngleZ: %f", camera.m_fAngleZ);
    if (ImGui::Button("Recentrer la scène")) {
      camera.defaultPosition();
    }
    if (ImGui::Button("Front")) {
      camera.posFront();
    }
    ImGui::SameLine();
    if (ImGui::Button("Back")) {
      camera.posBack();
    }
    if (ImGui::Button("Left")) {
      camera.posLeft();
    }
    ImGui::SameLine();
    if (ImGui::Button("Right")) {
      camera.posRight();
    }
    if (ImGui::Button("Top")) {
      camera.posTop();
    }
    ImGui::SameLine();
    if (ImGui::Button("Bottom")) {
      camera.posBottom();
    }
    ImGui::End();
  }

  void Interface::render(){
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }


} //namespace Imaker
