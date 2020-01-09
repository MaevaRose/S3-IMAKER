#include "class/File.hpp"

namespace Imaker {

    //Constructeur
    File::File() : world(World(25,25,25)), fileName("../Imaker/assets/data/NewFile.imaker") {
      world.createScene();
      world.getAllCubeTypes().push_back(cubeType(glm::vec3(0,0,1), "Bleu"));
      world.getAllCubeTypes().push_back(cubeType(glm::vec3(1,1,1), "Blanc"));
    };

    //Autre constructeur
    File::File(glm::vec3 tailleWorld) : world(World(tailleWorld.x, tailleWorld.y ,tailleWorld.z)), fileName("../Imaker/assets/data/NewFile.imaker") {
      world.createScene();
      world.getAllCubeTypes().push_back(cubeType(glm::vec3(0,0,1), "Bleu"));
      world.getAllCubeTypes().push_back(cubeType(glm::vec3(1,1,1), "Blanc"));
    }

    //Ouvrir un fichier .imaker
    void File::openFile(std::string File){
      std::string ligne;
      std::string mot;
      int nombre;
      int height = 0, width = 0, length = 0; // pour les valeurs de taille du monde
      int r = -1, g = -1, b = -1; //couleurs des types cubes
      int x = -1, y = -1, z = -1; // positions des cubes
      std::string typeName;

      //on ouvre le flux
    	std::string const openFileName(File);
    	std::ifstream file(openFileName.c_str());

      //vérification avant de continuer
      if(!file){std::cout<<"Impossible d'ouvrir le fichier"<<std::endl; exit(0);}

      fileName = openFileName;

      //le fichier commence par @IMAKER
      file.seekg(0, std::ios::beg);
      file>>mot;
      if(mot!="@IMAKER") { std::cout<<"erreur ligne 1"<<std::endl;}

      // On a une ligne dédié au monde
      file.seekg(1, std::ios::cur);
      file>>mot;
      if(mot!="World"){ std::cout<<"erreur ligne 2"<<std::endl;}
      else {
        //on vérifie et récupère les valeurs du monde
        //height du monde
        file.seekg(1, std::ios::cur);
        file>>nombre;
        if(!nombre) { std::cout<<"erreur height world"<<std::endl;}
        else { height = nombre;}
        //width du monde
        file.seekg(1, std::ios::cur);
        file>>nombre;
        if(!nombre) { std::cout<<"erreur width world"<<std::endl;}
        else { width = nombre;}
        //length du monde
        file.seekg(1, std::ios::cur);
        file>>nombre;
        if(!nombre) { std::cout<<"erreur length world"<<std::endl;}
        else { length = nombre;}

        //on peut maintenant créer le monde à partir des infos récupérées
        if(height != 0 && width != 0 && length != 0){ world = World(height, width, length);}
        else {std::cout<<"Erreur lors de la création de World"<<std::endl;}

      }

      ////////////////////////////////////////////////////////////////////////////////////
      //lignes suivantes dédiées aux typeCube/////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////////////
      //on lit le nombre de typeCube dans le monde
      file.seekg(1, std::ios::cur);
      int nbCubeType;
      file>>nbCubeType;
      if(!nbCubeType) { std::cout<<"erreur ligne 3"<<std::endl;}
      else {
        for(int i = 0 ; i < nbCubeType ; i++){
          //on lit chaque ligne avec ses trois couleurs et son nom    // Note : le nom est forcément en un seul morceau, l'utilisateur ne peut pas mettre d'espace
          file.seekg(1, std::ios::cur);
          file>>mot;
          if(mot!="Type"){ std::cout<<"erreur ligne Type"<<i<<std::endl;}
          //on est à la bonne itération
          file.seekg(1, std::ios::cur);
          file>>nombre;
          if(nombre != i) { std::cout<<"erreur ligne type"<<i<<std::endl;}
          //couleur r
          file.seekg(1, std::ios::cur);
          file>>nombre;
          if(nombre>255) { std::cout<<"erreur couleur r type"<<i<<std::endl;}
          else { r = nombre;}
          //couleur g
          file.seekg(1, std::ios::cur);
          file>>nombre;
          if(nombre>255) { std::cout<<"erreur couleur g type"<<i<<std::endl;}
          else { g = nombre;}
          //couleur b
          file.seekg(1, std::ios::cur);
          file>>nombre;
          if(nombre>255) { std::cout<<"erreur couleur b type"<<i<<std::endl;}
          else { b = nombre;}
          //typeName
          file.seekg(1, std::ios::cur);
          file>>typeName;
          //on vérifie et on push
          if(r != -1 && g != -1 && b != -1){
            char charTypeName[32];
    	      std::copy(typeName.begin(), typeName.end(), charTypeName);;
            world.getAllCubeTypes().push_back(cubeType(glm::vec3((float)r/255,(float)g/255,(float)b/255), charTypeName));
          }
        }
      }

      ////////////////////////////////////////////////////////////////////////////////////
      //lignes suivantes dédiées aux cubes/////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////////////
      int nbCubes;
      bool visible;
      file.seekg(1, std::ios::cur);
      file>>nbCubes;
      if(nbCubes != (height * width * length)) { std::cout<<"erreur ligne nombre cubes"<<std::endl;}
      else {
        for(int i = 0 ; i < nbCubes ; i++){
          file.seekg(1, std::ios::cur);
          file>>mot;
          if(mot!="Cube") { std::cout<<"erreur ligne cube"<<i<<std::endl;}
          //position x
          file.seekg(1, std::ios::cur);
          file>>x;
          if(x == -1){std::cout<<"erreur position x cube"<<i<<std::endl;exit(0);}
          //position y
          file.seekg(1, std::ios::cur);
          file>>y;
          if(y == -1){std::cout<<"erreur position y cube"<<i<<std::endl;exit(0);}
          //position z
          file.seekg(1, std::ios::cur);
          file>>z;
          if(z == -1){std::cout<<"erreur position z cube"<<i<<std::endl;exit(0);}
          //visible or not // Note : nous avons choisi de l'indiquer sous forme de string afin d'éviter un possible mélange avec la coordonnée z ou le numéro du type
          file.seekg(1, std::ios::cur);
          file>>mot;
          if(mot == "false") { visible = false; }
          else if(mot == "true") { visible = true; }
          else { std::cout<<"erreur visibilité cube"<<i<<std::endl; }
          //type
          file.seekg(1, std::ios::cur);
          file>>nombre;
          cubeType cubetype = world.getAllCubeTypes()[nombre];
          //on peut créer le cube
          world.getAllCubes()[y][z][x] = Cube(glm::vec3(y,z,x), visible, cubetype);
        }//fin de la boucle for pour chaque cube
      }
      ////////////////////////////////////////////////////////////////////////////////////
      //on vérifie qu'on a atteint la fin du document/////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////////////
      file.seekg(1, std::ios::cur);
      file>>mot;
      if(mot!="end") { std::cout<<"erreur ligne finale"<<std::endl;}
    }//fin de File::openFile(std::string File)


    //destructeur
    File::~File(){}

    //on vérifie si le fichier existe //implémenté pour le saveAs à l'origine
    bool File::fileExist(std::string File){
      std::string const openFileName(File);
    	std::ifstream file(openFileName.c_str());
      if(!file){return false;}
      else return true;
    }

    //sauvegarder le fichier
    void File::saveFile(std::string File){
      std::string const saveFileName(File);
      std::ofstream file(saveFileName.c_str());

      if(file){
        file << "@IMAKER" << std::endl;

        //World
        file << "World " << world.getHeight() << " " << world.getWidth() << " " << world.getLength() << " " << std::endl;

        //cubeType
        file << world.getAllCubeTypes().size() << std::endl;
        for(int i = 0 ; i < world.getAllCubeTypes().size() ; i++){
          file << "Type " << i << " " << int(world.getAllCubeTypes()[i].color.x*255) << " " << int(world.getAllCubeTypes()[i].color.y*255) << " " << int(world.getAllCubeTypes()[i].color.z*255) << " " <<  world.getAllCubeTypes()[i].name << " " << std::endl; //finir
        }

        //allCubes
        int nbCubes = world.getHeight() * world.getWidth() * world.getLength() ;
        file << nbCubes << std::endl;
        //boucle pour parcourir le vector à trois dimensions
        for(int i = 0 ; i < world.getWidth() ; i++ ){
            for(int j = 0 ; j < world.getLength() ; j++){
                for(int k = 0 ; k < world.getHeight() ; k++){
                  //on vérifie les valeurs de visible et de type qui sont stockées différemment
                  std::string stringVisible;
                  if(world.getAllCubes()[i][j][k].isVisible()) stringVisible = "true";
                  else stringVisible = "false";

                  int intCubeType;
                  for (int l = 0 ; l < world.getAllCubeTypes().size() ; l++) {
                    if(world.getAllCubes()[i][j][k].returnCubeType() == world.getAllCubeTypes()[l]) intCubeType = l;
                    else intCubeType = 0;
                  }

                  //on met le tout dans le fichier
                  glm::vec3 cubePosition = world.getAllCubes()[i][j][k].getPos();
                  file << "Cube " << cubePosition.z << " " << cubePosition.y << " " << cubePosition.x << " " << stringVisible << " " << intCubeType << " " << std::endl;
                }
            }
        }
        file << "end" << std::endl;
      }//if(file)
    }//void File::saveFile()


  std::string File::getFileName() {
    return fileName;
  }


  void File::changeFileName(std::string newName) {
    fileName = newName;
  }

} // namespace Imaker
