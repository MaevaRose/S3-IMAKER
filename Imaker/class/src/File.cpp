#include "class/File.hpp"

namespace Imaker {
File::File() : world(World(25,25,25)), fileName("NewFile") {
  world.createScene();
};

File::File(std::string openFile){
  std::string ligne;
  std::string mot;
  int nombre;
  int height = 0, width = 0, length = 0; // pour les valeurs de taille du monde
  int r = -1, g = -1, b = -1;
  int x = -1, y = -1, z = -1;
  std::string typeName;

  std::string chemin = "../Imaker/assets/data/";
	std::string fileImaker = chemin+openFile;
	std::cout<<fileImaker<<std::endl;

	std::string const fileName(fileImaker);
	std::ifstream file(fileName.c_str());

  if(!file){std::cout<<"Impossible d'ouvrir le fichier"<<std::endl; exit(0);}

  //le fichier commence par @IMAKER
  file.seekg(0, std::ios::beg);
  file>>mot;
  if(mot!="@IMAKER") { std::cout<<"erreur ligne 1"<<std::endl;}

  file.seekg(1, std::ios::cur);
  file>>nombre;
  if(!nombre) { std::cout<<"erreur ligne 1"<<std::endl;}

  // On a une ligne dédié au monde///////////////////////////////////////////////////////
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
      //on lit chaque ligne avec ses trois couleurs et son nom
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
        world.allCubeTypes.push_back(cubeType(glm::vec3((float)r/255,(float)g/255,(float)b/255), charTypeName));
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
      //visible or not
      file.seekg(1, std::ios::cur);
      file>>mot;
      if(mot == "false") { visible = false; }
      else if(mot == "true") { visible = true; }
      else { std::cout<<"erreur visibilité cube"<<i<<std::endl; }
      //type
      file.seekg(1, std::ios::cur);
      file>>nombre;
      cubeType cubetype = world.allCubeTypes[nombre];
      //on peut créer le cube
      world.allCubes[y][z][x] = Cube(glm::vec3(y,z,x), visible, cubetype);
      //std::cout<< "cube position " << x << y << z << "visible" << visible << std::endl;
    }//boucle for pour chaque cube
  }
  ////////////////////////////////////////////////////////////////////////////////////
  //on vérifie qu'on a atteint la fin du document/////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////
  file.seekg(1, std::ios::cur);
  file>>mot;
  if(mot!="end") { std::cout<<"erreur ligne finale"<<std::endl;}
}//fin de File::File(std::string openFile)


File::~File(){}

} // namespace Imaker
