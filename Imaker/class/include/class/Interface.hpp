#pragma once
#include <glimac/SDLWindowManager.hpp>
#include <iostream>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl.h>
#include <imgui/imgui_impl_opengl3.h>
#include <stdio.h>
#include <SDL.h>
#include "class/Cursor.hpp"

#include <GL/glew.h>


namespace Imaker{
  class Interface {
    public :
      Interface();
      ~Interface();
      void startFrame();
      void render();
      void swapBuffers();
      void selectionTypeCube(Cube &cube);

    public:
      glimac::SDLWindowManager windowManager;
      int typeCube;
  };
}