#include "class/Interface.hpp"



namespace Imaker{
  const int WINDOW_HEIGHT = 1000;
  const int WINDOW_WIDTH = 1000;
  bool browserIsOpen = false;
  bool createNewWorld = false;


  void sautDeLigne(int lignes){
    for(int i = 0 ; i < lignes ; i++){
      ImGui::Text(" ");
    }
  }

  Interface::Interface() : typeCube(0), currentColor(ImVec4(114.0f/255.0f, 144.0f/255.0f, 154.0f/255.0f, 255.0f/255.0f)), windowManager(glimac::SDLWindowManager(WINDOW_WIDTH, WINDOW_HEIGHT, "IMAKER - DURAND - ROSENBERG")) {
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

    SDL_StartTextInput();



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


  void Interface::selectionTypeCube(Cube &cube, World &world){
    ImGui::Begin("Cube Type");
    //ImGui::Button("Sélectionner Type!");
    ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_DisplayRGB;
    if (ImGui::TreeNode("Selection Type")){
      for (int n = 0; n < world.allCubeTypes.size(); n++)
      {
          if (ImGui::Selectable(world.allCubeTypes[n].name, n)){
            cube.editType(world.allCubeTypes[n]);
          }
      }
      ImGui::TreePop();
    }
    if(ImGui::TreeNode("Add New Type")){
      const char* label = "Test";
      //std::string* value;
      char value[32];
      ImGui::InputText(label, value, 32);
      ImGui::ColorPicker4("MyColor##4", (float*)&currentColor, flags, NULL);
      if (ImGui::Button("Add")) {
        //std::string temp_value = *value;
        world.createNewCubeType(glm::vec3(currentColor.x, currentColor.y, currentColor.z), value);
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

  void Interface::MainMenuBar(File &file){
    //menu bar de la démo
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New World", "")) {
              createNewWorld = true;
            }
            if (ImGui::MenuItem("Open World", "")) {
              browserIsOpen = true;
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
  }

void Interface::browserFile(File &file){
    // open Dialog Simple
     //ImGui::Begin("Open");
     if (browserIsOpen)
      ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".imaker\0\0", ".");

    // display
    if (ImGuiFileDialog::Instance()->FileDialog("ChooseFileDlgKey"))
    {
      // action if OK
      if (ImGuiFileDialog::Instance()->IsOk == true)
      {
        std::string filePathName = ImGuiFileDialog::Instance()->GetFilepathName();
        file.openFile(filePathName);
        // action
      }
      // close
      ImGuiFileDialog::Instance()->CloseDialog("ChooseFileDlgKey");
      browserIsOpen = false;
    }
    //ImGui::End();
  }

  void Interface::createNewWorldWindow(File &file){
    ImGui::SetNextWindowPos(ImVec2(WINDOW_HEIGHT/4, WINDOW_WIDTH/4), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(WINDOW_HEIGHT/2, WINDOW_WIDTH/2), ImGuiCond_FirstUseEver);
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
    if (createNewWorld){
      static int height = 25, width = 25, length = 25;

      ImGui::Begin("Create New World", NULL, window_flags);
        sautDeLigne(8);
        ImGui::SameLine(150); ImGui::Text("Créez un nouveau monde !");
        sautDeLigne(3);
        ImGui::SameLine(80); ImGui::SliderInt("Hauteur", &height, 1, 50);
        sautDeLigne(1);
        ImGui::SameLine(80); ImGui::SliderInt("Largeur", &width, 1, 50);
        sautDeLigne(1);
        ImGui::SameLine(80); ImGui::SliderInt("Longueur", &length, 1, 50);
        sautDeLigne(6);
        if (ImGui::Button("Annuler")) {
          createNewWorld = false;
        }
        ImGui::SameLine(100);
        if (ImGui::Button("Créer monde")) {
          file = File(glm::vec3(height, width, length));
          createNewWorld = false;
        }
      ImGui::End();
    }
  }

  void Interface::render(){
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }


} //namespace Imaker
