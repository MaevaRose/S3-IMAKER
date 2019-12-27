#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <class/World.hpp>


namespace Imaker{
  class File {
    public :
      File();
      File(glm::vec3 tailleWorld);
      ~File();
      void openFile(std::string File);
      void createWorldFromFile();
      bool fileExist(std::string File);
      void saveFile(std::string File);

    public :
      //glm::vec3 sizeWorld;
      World world;
      std::string fileName;

  };
}
