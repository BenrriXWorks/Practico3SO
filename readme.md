## Aplicacion de menu con inicio de sesion y funciones
Esta aplicacion permite realizar un login y cargar un menu con
funciones dependientes de los permisos del usuario.
Esta aplicacion contiene los siguientes componentes independientes:
- Login, Menu(main), Indexer, IndexInverter, TreeFilesystem, CircleFilesystem & Plotter.
Nota: Cada componente en Components cuenta con un readme para su uso individual.

# Actualizaciones Nuevas
- Se agregaron las opciones al menu:
    -Crear carpetas basado en sistema de archivos de arbol
        Permite crear un directorio basado en sistema de archivos de arbol a partir de un archivo .dit
        Se encuentra ubicado en Components/TreeFilesystem/main
        Su llamada individual desde su carpeta es: $ ./main path donde path es la ubicacion del archivo .dit

    -Crear carpetas basado en sistema de archivos de lista circular
        Permite crear un directorio basado en sistema de archivos de lista circular a  partir de un archivo .dre
        Se encuentra ubicado en Components/CircleFilesystem/main
        Su llamada individual desde su carpeta es: $ ./main path N R donde path es la ubicacion del archivo .dre
        N es el numero maximo de directorios permitidos y 
        R es el numero maximo de archivos permitidos por directorio

    -Mostrar grafico de los puntos entregados
        Permite crear un grafico a partir de un archivo .gra
        Se encuentra ubicado en Components/Plotter/main
        Su llamada individual desde su carpeta es: $ ./main path donde path es la ubicacion del archivo .gra
    
    Se agregaron las variables de entorno 
        TREE_FILESYSTEM_INPUT_ROUTE, TREE_FILESYSTEM_EXEC_ROUTE,
        DIR_MAX_CIRCLE_FILESYSTEM, AR_MAX_CIRCLE_FILESYSTEM, DIR_CIRCLE_EXEC_ROUTE, DIR_CIRCLE_INPUT_ROUTE,
        PLOTTER_EXEC_ROUTE, PLOTTER_WINDOW_SIDE_SIZE, PLOTTER_PADDING
    Todas relacionadas con los puntos anteriores en el mismo orden ^
    
- Se pueden leer nuevos tipos de archivos:
    .dit: Archivo de arbol de directorio
    .dre: Archivo de lista circular de directorio
    .gra: Archivo de puntos para graficacion
Hay una documentacion detallada acerca de estos archivos en los readme de los componentes dedicados a cada tipo,
TreeFilesystem, CircleFilesystem & Plotter.


# Descripcion:
- Se leen los argumentos del archivo .env
- Se inicia sesion con el modulo de login y se recibe un token encriptado.
- Se lee la respuesta y se crea el usuario.
- Se inicia un menu con las opciones disponibles.

# Configuracion:
No se debe alejar la carpeta libraries.
- Se puede modificar el programa con:
- .env (para las rutas y variables) respetando el formato estandar de un archivo ENV.
- data/Options.txt: Cambiar las opciones del menu {n_opcion,texto_opcion,funcion_opcion}
    ej: 0,Salir del programa,salir
- data/Permissions.txt: Cambiar los permisos por tipo de perfil {tipo;n_permisos}, si n_permisos=* entonces son todos, no se incluye el permiso 0.
    ej: rookie;1,2,3
- data/Users.txt: Agregar usuarios {nombre,perfil}
    ej: benjamin,admin

# Variables de entorno:
*Obligatorias*
{
    // Antiguas
    EXTENTION: Extension de los archivos a indexar
    PATH_FILES_IN: Path de los archivos a indexar
    PATH_FILES_OUT: Path de salida de los archivos indexados
    AMOUTN_THREADS: Cantidad de threads para indexar
    INVERTED_INDEX_FILE: Ruta donde se guardara/leera el indice invertido
    USERS_DB: Ruta del archivo de base de datos de usuarios
    PERMISSIONS_DB: Ruta del archivo de base de datos de permisos
    OPTIONS_DB: Ruta del archivo de base de datos de opciones
    LOGIN_EXECUTABLE: Ruta del ejecutable del componente de login
    INVERTED_INDEXER_PATH: Ruta a la carpeta donde se encuentra el main del indice invertido
    TOPK: Resultados a mostrar en el buscador
    INDEXER_PATH: Path al creador del indice donde iniciar el ./main

    // Nuevas
    DIR_MAX_CIRCLE_FILESYSTEM: Numero maximo de directorios que se crearan
    AR_MAX_CIRCLE_FILESYSTEM: Numero maximo de archivos que se crearan por directorio
    DIR_CIRCLE_INPUT_ROUTE: Ruta del archivo .dre
    DIR_CIRCLE_EXEC_ROUTE: Ruta del main del creador de carpetas de lista circular
    PLOTTER_EXEC_ROUTE: Ruta del main del graficador 
    PLOTTER_WINDOW_SIDE_SIZE: De que porte en pixeles sera la ventana del graficador
    PLOTTER_PADDING: Cuanto padding tendra la ventana del graficador
    TREE_FILESYSTEM_EXEC_ROUTE: Ruta del main del creador de carpetas por arbol de indices
}
*Opcionales* 
{
    AT_LEAST_20_FILES_INDEX:1 Si se quiere hacer el indice con minimo 20 archivos
}

# Compilado
Simplemente se ejecuta make desde la carpeta base del programa asi: $ make
El make ejecutara consecutivamente los make de la carpeta Components y dejara a disposicion el del menu.

# Uso:
En linux se puede ejecutar asi:
    ./main -u "nombreUsuario" -i "archivo/para/contar.txt" -o "salida/Archivo/contar.txt" -f "archivo/para/crear.txt" -t "textoParaAgregar" -v "n1;n2;...;n4"
El unico argumento obligatorio para iniciar es -u

# External
Para el completo funcionamiento se requiere tener instalado X11 (para el proceso externo Graficador) y tree (para los procesos externos sistema de archivos de arbol y sistema de archivos de lista circular)
para instalar en linux ejecute
$ sudo apt-get install libx11-dev
$ sudo apt-get install tree
