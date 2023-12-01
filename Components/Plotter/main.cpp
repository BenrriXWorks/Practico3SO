#include "include/Plotter.h"
#include "include/FileReader.h"
#include "include/Functions.h"

using namespace std;

int main(int argc, char** argv){

    // Leer los argumentos
    if (argc != 2){
        printf("Debes ingresar la ruta del archivo de puntos\n");
        return EXIT_FAILURE;
    }

    // Conseguir la ruta y verificar la extension
    std::string route = argv[1];
    if (route.size() < 4 || route.substr(route.size()-3) != "gra"){
        printf("El archivo de grafico debe ser de extension .gra\n");
        return EXIT_FAILURE;
    }

   

    // Leer las variables de entorno
    vector<const char*> envNames {
        "WINDOW_SIZE",
        "PADDING"
    };
    // Si faltan, leerlas desde el archivo .env
    if (any_of(envNames.begin(), envNames.end(), [](auto x){return !getenv(x);})){
     // Leer rapidamente las variables de entorno del archivo si es necesario
        FileReader envFileReader;
        envFileReader.open(".env");
        for (const auto& line : envFileReader.readLines()){
            auto [key, value] = split1(line, '=');
            setenv(key.c_str(), value.c_str(), 1);
        }
        envFileReader.close();
    }
    // Si aun asi falta alguna, decir cual y retornar error.
    for (auto s : envNames){
        if (!getenv(s)){
            printf("Falta la variable de entorno %s\n", s);
            return EXIT_FAILURE;
        }
    }

    // Establecer margenes seguros de pantalla y padding
    int padding = stoi(getenv("PADDING")), windowSize = stoi(getenv("WINDOW_SIZE"));
    if (padding > 100 || padding < 30){
        printf("Se dejara el padding en los margenes seguros [30-100]\n");
        char newPadding[4];
        padding = max(30, min(100, padding));
        sprintf(newPadding,"%d", padding);
        setenv("PADDING", newPadding, true);
    }
    if (windowSize < 500){
        printf("El tamano minimo permitido es 500x500px, reescalando\n");
        char newWindowSize[4];
        sprintf(newWindowSize, "%d", 500);
        setenv("WINDOW_SIZE", newWindowSize, true);
    }

    // Leer el archivo de datos
    FileReader fileReader;
    if (!fileReader.open(route)){
        printf("No se pudo leer el archivo de puntos\n");
        return EXIT_FAILURE;
    }
    // Interpretar el archivo de entrada y validar su formato (EL Titulo puede estar vacio)
    vector<pair<float, float>> points;
    string title;
    int nline = 0;
    try{
        auto [titleKey, titlevalue] = split1(fileReader.readLine(), ':');
        if (titleKey != "titulo") throw runtime_error("Debe ingresar el titulo en la primera linea asi: titulo:{TITULO}");
        title = stripAllOf(titlevalue, "\"'");
        
        for (const auto& line : fileReader.readLines()){
            ++nline;
            // En caso de lineas vacias se salta
            if (line.empty()) continue;
            // Sacar los valores de la forma x:n,y:n
            auto [xstr, ystr] = split1(line, ',');
            auto [xkey, xvalue] = split1(xstr, ':');
            auto [ykey, yvalue] = split1(ystr, ':'); 
            if (xkey != "x" || ykey != "y") 
                throw runtime_error("No se respeto el formato x:n,y:n del archivo de entrada");
            // Revisar que no se salga del dominio
            if (atof(xvalue.c_str()) > 100 || atof(xvalue.c_str()) < 0 || atof(yvalue.c_str()) > 100 || atof(yvalue.c_str()) < 0){
                printf("El punto (%f, %f) se sale del dominio de [(x,y) | x <- [0..100], y <- [0..100]\n", stof(xvalue.c_str()), stof(yvalue.c_str()));
                throw runtime_error("Punto fuera de dominio establecido\n");
            }
            points.push_back(make_pair(stof(xvalue), stof(yvalue)));
        }
    } catch(exception &e){
        printf("El archivo de entrada no cumple con el formato establecido\n");
        printf("Error especifico: %s\n", e.what());
        printf("Revisar en la linea %d\n", nline);
        return EXIT_FAILURE;
    }


    // Ordenar los puntos (comparando con la clave x)
    //auto pointsComparator = [](pair<float, float> p1, pair<float, float> p2){ return p1.first < p2.first; };
    //sort(execution::par, points.begin(), points.end(), pointsComparator);

    // Crear el grafico
    plot(points, title.c_str());
    printf("Grafico cerrado!\n");

    return EXIT_SUCCESS;

}