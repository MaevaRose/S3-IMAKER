#pragma once
#include <glimac/SDLWindowManager.hpp>
#include <glimac/TrackBallCamera.hpp>
#include <iostream>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_stdlib.h>
#include <imgui/ImGuiFileDialog.h>
#include <stdio.h>
#include <SDL.h>
#include "class/Cursor.hpp"
#include "class/RBF.hpp"
#include "class/File.hpp"

#include <GL/glew.h>


namespace Imaker{
  class Interface {
    public :
      Interface();
      ~Interface();
      void startFrame();
      void render();
      void swapBuffers();
      void selectionTypeCube(Cube &cube, World &world);
      void posCamera(TrackBallCamera &camera, int &luminosity);
      void MainMenuBar(File &file);
      void browserFile(File &file);
      void createNewWorldWindow(File &file, Cursor &cursor);
      void saveWindow();
      void saveAsWindow(File &file);
      void overwriteWindow(File &file);
      void rbfWindow(File &file, InterpolationFunc &fonction);
      void draw(TrackBallCamera &camera, File &currentFile, Cursor &cursor, int &luminosity, InterpolationFunc &fonction);

    public:
      glimac::SDLWindowManager windowManager;
      ImGuiIO io;
      int typeCube;
      ImVec4 currentColor;
  };
}
