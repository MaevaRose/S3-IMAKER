#include "class/Interface.hpp"



namespace Imaker{
  const int WINDOW_HEIGHT = 1000;
  const int WINDOW_WIDTH = 1000;
  bool browserIsOpen = false;
  bool createNewWorld = false;
  bool save = false;
  bool saveAs = false;
  bool changeFileName = false;
  bool overwrite = false;


  //pour aligner verticalement dans la fenêtre
  void sautDeLigne(int lignes){
    for(int i = 0 ; i < lignes ; i++){
      ImGui::Text(" ");
    }
  }



  //constructeur
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



  //destruteur
  Interface::~Interface(){
      ImGui_ImplOpenGL3_Shutdown();
      ImGui_ImplSDL2_Shutdown();
      ImGui::DestroyContext();

      SDL_GL_DeleteContext(windowManager.openglContext);
      SDL_DestroyWindow(windowManager.window);
      SDL_Quit();
    }



  // dessiner avec imgui
  void Interface::startFrame(){
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(windowManager.window);
    ImGui::NewFrame();
  }



  //Fenêtre pour les types de Cubes
  void Interface::selectionTypeCube(Cube &cube, World &world){
    ImGui::Begin("Cube Type");
    ImGuiColorEditFlags colorFlags = ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_DisplayRGB;
    if (ImGui::TreeNode("Tous les types")){
      for (int n = 0; n < world.getAllCubeTypes().size(); n++)
      {
          const char* charCubeType = world.getAllCubeTypes()[n].name.c_str();
          if (ImGui::Selectable(charCubeType, n)){
            cube.editType(world.getAllCubeTypes()[n]);
          }
      }
      ImGui::TreePop();
    }
    if(ImGui::TreeNode("Ajouter un nouveau type")){
      static char nomTypeCube[32] = "";
      static ImGuiInputTextFlags textFlags = ImGuiInputTextFlags_AllowTabInput | ImGuiInputTextFlags_CharsNoBlank;
      ImGui::InputText("  ", nomTypeCube, 64, textFlags);
      ImGui::ColorPicker4("MyColor##4", (float*)&currentColor, colorFlags, NULL);
      if (ImGui::Button("Add")) {
        world.createNewCubeType(glm::vec3(currentColor.x, currentColor.y, currentColor.z), nomTypeCube);
      }
      ImGui::TreePop();
    }

    ImGui::End();
  }



  //fenêtre de positions par défaut pour la caméra
  void Interface::posCamera(TrackBallCamera &camera, int &luminosity){
    ImGui::Begin("Camera");
    ImGui::Text("m_fAngleX: %f", camera.m_fAngleX);
    ImGui::Text("m_fAngleZ: %f", camera.m_fAngleZ);
    //les boutons
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
    ImGui::SliderInt("Luminosité", &luminosity, 0, 10000);
    ImGui::End();
  }



  //barre de menu en haut de la fenêtre
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
            if (ImGui::MenuItem("Save", "")) {
              file.saveFile(file.getFileName());
              save = true;
              saveAs = false;
            }
            if (ImGui::MenuItem("Save As", "")) {
              saveAs = true;
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
  }



  //fenêtre pour se déplacer dans les fichiers
  void Interface::browserFile(File &file){
       if (browserIsOpen)
        ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".imaker\0\0", "."); // filtrage pour ne voir que les fichiers .imaker

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
    }




  //créer un nouveau monde avec les valeurs de notre choix
  void Interface::createNewWorldWindow(File &file, Cursor &cursor){
    ImGui::SetNextWindowPos(ImVec2(WINDOW_HEIGHT/4, WINDOW_WIDTH/4), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(WINDOW_HEIGHT/2, WINDOW_WIDTH/2), ImGuiCond_FirstUseEver);
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
    if (createNewWorld){
      static int height = 25, width = 25, length = 25;

      ImGui::Begin("Create New World", NULL, window_flags);
        sautDeLigne(8);
        ImGui::SameLine(150); ImGui::Text("Créez un nouveau monde !");
        sautDeLigne(3);
        ImGui::SameLine(80); ImGui::SliderInt("Hauteur", &height, 3, 50);
        sautDeLigne(1);
        ImGui::SameLine(80); ImGui::SliderInt("Largeur", &width, 3, 50);
        sautDeLigne(1);
        ImGui::SameLine(80); ImGui::SliderInt("Longueur", &length, 3, 50);
        sautDeLigne(6);
        if (ImGui::Button("Annuler")) {
          createNewWorld = false;
        }
        ImGui::SameLine(100);
        if (ImGui::Button("Créer monde")) {
          file = File(glm::vec3(height, width, length));
          createNewWorld = false;
          cursor.resetPos();
        }
      ImGui::End();
    }
  }



  //une fenêtre pop up pour indiquer que le fichier a été sauvegardé
  void Interface::saveWindow(){
    ImGui::SetNextWindowPos(ImVec2(WINDOW_HEIGHT/4, WINDOW_WIDTH/4), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(WINDOW_HEIGHT/2, WINDOW_WIDTH/2), ImGuiCond_FirstUseEver);
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
    if (save){
      ImGui::Begin("Fichier sauvegardé", NULL, window_flags);
      sautDeLigne(10);
      ImGui::SameLine(150); ImGui::Text("Fichier sauvegardé !");
      sautDeLigne(5);
      ImGui::SameLine(150);
      if (ImGui::Button("Continuer")) {
        save = false;
      }
      ImGui::End();
    }
  }

  // fenêtre pop up pour s'assurer que l'utilisateur est conscient qu'il écrase un fichier
  void Interface::overwriteWindow(File &file){
    ImGui::SetNextWindowPos(ImVec2(WINDOW_HEIGHT/4, WINDOW_WIDTH/4), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(WINDOW_HEIGHT/2, WINDOW_WIDTH/2), ImGuiCond_FirstUseEver);
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
    if (overwrite){
      ImGui::Begin("Ecraser fichier", NULL, window_flags);
      sautDeLigne(10);
      ImGui::SameLine(10); ImGui::Text("Ce fichier existe déjà. Voulez-vous l'écraser par celui-ci ?");
      ImGui::Text(" "); ImGui::SameLine(50); ImGui::Text("(c'est violent quand même...)");
      sautDeLigne(5);
      ImGui::SameLine(150);
      if (ImGui::Button("Continuer")) {
        file.saveFile(file.getFileName());
        save = true;
        overwrite = false;
        saveAs = false;
      }
      ImGui::SameLine(20);
      if (ImGui::Button("Annuler")) {
        save = false;
        saveAs = false;
        overwrite = false;
      }
      ImGui::End();
    }
  }



  void Interface::saveAsWindow(File &file){
    if (saveAs){
      ImGui::SetNextWindowPos(ImVec2(WINDOW_HEIGHT/4, WINDOW_WIDTH/4), ImGuiCond_FirstUseEver);
      ImGui::SetNextWindowSize(ImVec2(WINDOW_HEIGHT/2, WINDOW_WIDTH/2), ImGuiCond_FirstUseEver);
      ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse;
      static char nomFichier[32] = "";
      static ImGuiInputTextFlags textFlags = ImGuiInputTextFlags_AllowTabInput | ImGuiInputTextFlags_CharsNoBlank;

      ImGui::Begin("Nouveau nom de fichier", NULL, window_flags); sautDeLigne(10);
      ImGui::Text("Nouveau nom de fichier :"); ImGui::SameLine(15); ImGui::InputText("  ", nomFichier, 64, textFlags); sautDeLigne(5); ImGui::SameLine(150);
      if (ImGui::Button("Valider")) {
        std::string temp_string(nomFichier);
        std::string newFileName = "../Imaker/assets/data/" + temp_string + ".imaker";
        if(file.fileExist(newFileName)) {
          overwrite = true;
          file.changeFileName(newFileName);
        }
        else {
          file.changeFileName(newFileName);
          file.saveFile(newFileName);
          save = true;
          overwrite = false;
          saveAs = false;
        }
      }
      ImGui::SameLine(20);
      if (ImGui::Button("Annuler")){
        saveAs = false;
      }
      ImGui::End();
    }
  }

  void Interface::rbfWindow(File &file, InterpolationFunc &fonction){
    static float  coeff = 0.123f;
    static bool inputs_step = true;
    const float   f32_zero = 0.f, f32_one = 1.f;
    static int selected = -1;
    static int poids[3] = { 1, 1, 1 };
    static int x = 0, y = 0, z = 0;
    ImGui::Begin("Génération de terrain");
    if (ImGui::TreeNode("Fonctions procédurales :"))
    {
        if (ImGui::Selectable("Linéaire", selected==1 )) selected = 1;
        if (ImGui::Selectable("MultiQuad", selected == 2)) selected = 2;
        if (ImGui::Selectable("InverseQuad", selected == 3)) selected = 3;
        if (ImGui::Selectable("InverseMultiQuad", selected == 4)) selected = 4;
        if (ImGui::Selectable("Gauss", selected == 5)) selected = 5;
        ImGui::Text("Coefficient :"); ImGui::SameLine(); ImGui::InputScalar("input float",   ImGuiDataType_Float,  &coeff, inputs_step ? &f32_one : NULL);
        if(fonction.returnContraintes().size() > 0)
        {
          if (ImGui::Button("Générer")) {
            file.world.reset();
            fonction.setAlpha(coeff);
            fonction.setIndice(selected);
            fonction.calculW(fonction.buildMatContrainte());
            fonction.drawFunc(file.world);
          }
        }
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("Modifier les contraintes"))
    {
        ImGui::Text("Toutes les contraintes :");
        static int selectContr = -1;
        for (int n = 0; n < fonction.returnContraintes().size(); n++)
        {
            char buf[32];
            sprintf(buf, "Contrainte %d : ", n);
            if (ImGui::Selectable(buf, selectContr == n))
                selectContr = n;
        }
        if(fonction.returnContraintes().size() > 0){
          if (ImGui::Button("Supprimer")) {
            fonction.deleteContraintes(selectContr);
          }
        }


        //ImGui::SliderInt3(" ", poids, 0, file.world.getWidth(), file.world.getLength(), file.world.getHeight());
        ImGui::SliderInt("x", &x, 0, file.world.getLength()); ImGui::Text(" ");
        ImGui::SameLine(30); ImGui::SliderInt("y", &y, 0, file.world.getHeight());ImGui::Text(" ");
        ImGui::SameLine(30);ImGui::SliderInt("z", &z, 0, file.world.getWidth());
        if (ImGui::Button("Ajouter")) {
          file.world.reset();
          fonction.addContrainte(x, y, z);
          fonction.setAlpha(coeff);
          fonction.setIndice(selected);
          fonction.calculW(fonction.buildMatContrainte());
          fonction.drawFunc(file.world);
        }
        ImGui::TreePop();
    }
    ImGui::End();
  }

  //dessin de l'Interface
  void Interface::draw(TrackBallCamera &camera, File &currentFile, Cursor &cursor, int &luminosity, InterpolationFunc &fonction){
    glm::vec3 cursorPos = cursor.getCursorPos();
    startFrame();
    //toutes les fenêtres
    rbfWindow(currentFile, fonction);
    posCamera(camera, luminosity);
    MainMenuBar(currentFile);
    browserFile(currentFile);
    saveWindow();
    saveAsWindow(currentFile);
    overwriteWindow(currentFile);
    createNewWorldWindow(currentFile, cursor);
    selectionTypeCube(currentFile.world.getAllCubes()[cursorPos.x][cursorPos.y][cursorPos.z], currentFile.world);
  }

  //rendu de l'interface
  void Interface::render(){
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  }



} //namespace Imaker
