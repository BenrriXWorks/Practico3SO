#include "../../include/DirCircle.h"



DirCircle* DirCircle::fromFile(std::string route, std::string extension){

    std::string filename = route.substr(route.find_last_of("\\/")+1);
    std::string fileExtension = filename.substr(filename.find_last_of('.')+1);

    if(fileExtension != extension){
        printf("Extensión del archivo indicado es inválida\n");
        return nullptr;
    }

    DirCircle* dirCircle = new DirCircle();
    if(!dirCircle->process(route)) return nullptr;
    

    // Procesar el contenido del archivo y llenar dirCircle->dirbase y dirCircle->dirs

    return dirCircle;

}

bool DirCircle::process(std::string path){
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
            dirs[dir] = split(files, ';');
        }
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
        printf("Error al crear el directorio base");
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
                printf("Error al crear el directorio %s",dirPath.c_str());
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