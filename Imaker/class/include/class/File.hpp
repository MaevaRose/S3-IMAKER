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
      void changeFileName(std::string);
      std::string getFileName();

    public :
      World world;

    private :
      std::string fileName;

  };
}
