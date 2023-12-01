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
    if (line.find("dirbase=./") == 0) {
        dirbase = line.substr(10);
    }
    else{
        printf("Formato del archivo %s invalido\n",path.c_str());
        return false;
    } 
    
    if (reader.checkDirectory(dirbase)){
        printf("El directorio base '%s' ya existe, elige otro!\n",dirbase.c_str());
        return false;
    }
    

    // Leer dirs
    line = reader.readLine();
    if (line.find("dirs=") == 0) {
        std::string dirsLine = line.substr(5);
        std::istringstream dirsStream(dirsLine);

        // Obtener claves de dirs
        std::string dir;
        std::string acc = "";
        while (std::getline(dirsStream, dir, ';')) {
            dirs[dir] = std::vector<std::string>();
            rutas[dir] = acc + dir;
            acc +=  dir + "/";
            
        }
        if(dirs.size() >(size_t)N){
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
            if(archivos.size() > (size_t)R){
                printf("Se excedio el maximo de archivos\n");
                return false;
            }
            if(dirs.find(dir) != dirs.end())
                dirs[dir] = archivos;
            else
                printf("Directorio %s no fue declarado, saltando...\n",dir.c_str());
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
    
    std::string acc = "";
    for (; it != dirs.end(); ++it) {
        std::istringstream iss(rutas[it->first]);
        std::string subdir;
        while (std::getline(iss, subdir, ';')) {
            std::string dirPath = dirbase + subdir;
            if (mkdir(dirPath.c_str(), 0777) == -1) {
                printf("Error al crear el directorio %s\n",dirPath.c_str());
                if(!system(("rm -r "+ dirbase).c_str()))
                    printf("Error al borrar el directorio base\n");
                printf("Abortando...\n");
                exit(EXIT_FAILURE);
            }
            
            acc += "../";
            
        }
    }
    //se crea un link virtual si es que hay mas de un directorio
    if(dirs.begin()->first != lastIt->first)
        std::filesystem::create_directory_symlink(acc + dirs.begin()->first, dirbase + rutas[lastIt->first]+"/link_to_first");
     

}

void DirCircle::createFiles() {
    // Crear archivos en los directorios señalados
    for (const auto& entry : dirs) {
        std::string dirPath = dirbase + rutas[entry.first] + "/";
        for (const auto& file : entry.second) {
            std::ofstream outfile(dirPath + file);
            outfile.close();
        }
    }
}