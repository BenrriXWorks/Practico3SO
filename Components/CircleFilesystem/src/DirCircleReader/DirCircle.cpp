#include "../../include/DirCircle.h"



DirCircle* DirCircle::fromFile(std::string route, std::string extension, int N , int R){

    std::string filename = route.substr(route.find_last_of("\\/")+1);
    std::string fileExtension = filename.substr(filename.find_last_of('.')+1);

    if(fileExtension != extension){
        printf("Extensión del archivo indicado es inválida\n");
        return nullptr;
    }

    DirCircle* dirCircle = new DirCircle();
    if(!dirCircle->process(route,N,R) )return nullptr;
    

    // Procesar el contenido del archivo y llenar dirCircle->dirbase y dirCircle->dirs

    return dirCircle;

}

bool DirCircle::process(std::string path,int N , int R){
    // Utiliza FileReader para abrir y leer el archivo
    FileReader reader;
    if (!reader.open(path)) {
        printf("Error al abrir el archivo %s\n",path.c_str());
        return false;
    }

    std::string line;

    // Leer dirbase
    line = reader.readLine();
    if (line.find("dirbase=") == 0) {
        dirbase = line.substr(8);
    }
    else{
        printf("Formato del archivo %s invalido\n",path.c_str());
        return false;
    } 

    // Leer dirs
    line = reader.readLine();
    if (line.find("dirs=") == 0) {
        std::string dirsLine = line.substr(5);
        std::istringstream dirsStream(dirsLine);

        // Obtener claves de dirs
        std::string dir;
        while (std::getline(dirsStream, dir, ';')) {
            dirs[dir] = std::vector<std::string>();
        }
        if(dirs.size() >N){
            printf("Se excedio el maximo de directorios\n");
            return false;
        }

        // Leer y asociar valores a las claves
        while (!reader.eof()) {
            line = reader.readLine();
            std::istringstream fileStream(line);

            // Obtener el nombre del directorio
            std::getline(fileStream, dir, '=');

            // Obtener los archivos asociados al directorio
            std::string files;
            std::getline(fileStream, files);

            // Agregar los archivos al vector asociado a la clave
            std::vector< std::string > archivos = split(files, ';');
            if(archivos.size() > R){
                printf("Se excedio el maximo de archivos");
                return false;
            }
            dirs[dir] = archivos;
        }
    }
    else{
        printf("Formato del archivo %s invalido\n",path.c_str());
        return false;
    } 

    reader.close();
    return true;

}

void DirCircle::createDir()
{

    
    createSubdirs();
    createFiles();

    /*printf("Dir base = %s\n",dirbase.c_str());
    printf("\n");
    for (const auto& entry : dirs) {
        printf("Directorio %s\n", entry.first.c_str());

        printf("Archivos:\n");
            for (const auto& file : entry.second) {
                printf("  %s\n", file.c_str());
            }
    }*/

}

void DirCircle::createSubdirs() {
    // Crear directorio base
    if (mkdir(dirbase.c_str(), 0777) == -1) {
        printf("Error al crear el directorio base\n");
        exit(EXIT_FAILURE);
    }

    // Crear subdirectorios y enlaces virtuales
    auto it = dirs.begin();
    auto lastIt = std::prev(dirs.end());
    

    for (; it != dirs.end(); ++it) {
        std::istringstream iss(it->first);
        std::string subdir;
        while (std::getline(iss, subdir, ';')) {
            std::string dirPath = dirbase + subdir;
            if (mkdir(dirPath.c_str(), 0777) == -1) {
                printf("Error al crear el directorio %s\n",dirPath.c_str());
                exit(EXIT_FAILURE);
            }
            
            
        }
    }
    std::filesystem::create_directory_symlink("../" + dirs.begin()->first,dirbase + lastIt->first+"/link_to_first");
     

}

void DirCircle::createFiles() {
    // Crear archivos en los directorios señalados
    for (const auto& entry : dirs) {
        std::string dirPath = dirbase + entry.first + "/";

        for (const auto& file : entry.second) {
            std::ofstream outfile(dirPath + file);
            outfile.close();
        }
    }
}