**Aplicacion de menu con inicio de sesion y funciones**
Esta aplicacion permite realizar un login y cargar un menu con
funciones dependientes de los permisos del usuario.
Esta aplicacion contiene los siguientes componentes independientes:
- Login, Menu, Indexer & IndexInverter.
Nota: Cada componente en Components cuenta con un readme para su uso individual.

*Actualizacion*
- Se agrego la opcion al menu llamarBuscador, que permite hacer busquedas sobre el indice
invertido creado. Es un proceso externo ubicado en Components/BenrrixInvertedSearcher/main.
Su llamada individual desde su carpeta es: $ ./main pathIndex topk, donde pathIndex es la ubicacion
del archivo de indice invertido, y topk (num > 4) indica la cantidad de resultados a mostrar en pantalla.
Hay una documentacion un poco mas detallada en el readme especifico del componente.
- Se agrego la variable de entorno TOPK que esta relacionado con el punto anterior ^.
- Se creo una restriccion artificial a la funcion indexadora principal que revisa que los
archivos a leer sean de tamano mayor a 1 MB.

*Actualizaciones Nuevas*
- Se agregaron las opciones al menu:
    -Crear carpetas basado en sistema de archivos de arbol
        Permite crear un directorio basado en sistema de archivos de arbol a partir de un archivo .dit
        Se encuentra ubicado en Components/TreeFilesystem/main
        Su llamada individual desde su carpeta es: $ ./main path donde path es la ubicacion del archivo .dit

    -Crear carpetas basado en sistema de archivos de lista circular
        Permite crear un directorio basado en sistema de archivos de lista circular a  partir de un archivo .dre
        Se encuentra ubicado en Components/CircleFilesystem/main
        Su llamada individual desde su carpeta es: $ ./main path  N R donde path es la ubicacion del archivo .dre
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
    Todas relacionadas con los puntos anteriores ^

    Hay una documentacion mas detallada en el readme especifico de cada componente

*Descripcion:*
- Se leen los argumentos del archivo .env
- Se inicia sesion con el modulo de login y se recibe un token encriptado.
- Se lee la respuesta y se crea el usuario.
- Se inicia un menu con las opciones disponibles.

*Configuracion:*
No se debe alejar la carpeta libraries.
- Se puede modificar el programa con:
- .env (para las rutas y variables) respetando el formato estandar de un archivo ENV.
- data/Options.txt: Cambiar las opciones del menu {n_opcion,texto_opcion,funcion_opcion}
    ej: 0,Salir del programa,salir
- data/Permissions.txt: Cambiar los permisos por tipo de perfil {tipo;n_permisos}, si n_permisos=* entonces son todos, no se incluye el permiso 0.
    ej: rookie;1,2,3
- data/Users.txt: Agregar usuarios {nombre,perfil}
    ej: benjamin,admin
Por defecto, todos estos archivos menos el .env se encuentran en data/ y los componentes en Components, pero se puede modificar alterando el .env.
Las variables de entorno necesarias para el funcionamiento completo son:
{EXTENTION, PATH_FILES_IN, PATH_FILES_OUT, AMOUTN_THREADS, INVERTED_INDEX_FILE, USERS_DB, PERMISSIONS_DB, OPTIONS_DB,
INDEXER_PATH, LOGIN_EXECUTABLE, INVERTED_INDEXER_PATH, TOPK, DIR_MAX_CIRCLE_FILESYSTEM, AR_MAX_CIRCLE_FILESYSTEM, DIR_CIRCLE_INPUT_ROUTE, DIR_CIRCLE_EXEC_ROUTE, PLOTTER_EXEC_ROUTE, PLOTTER_WINDOW_SIDE_SIZE, PLOTTER_PADDING, TREE_FILESYSTEM_INPUT_ROUTE, TREE_FILESYSTEM_EXEC_ROUTE}.
y las opcionales son:
{AT_LEAST_20_FILES_INDEX}
Nota: Las funciones relacionadas con la indexacion llaman procesos externos, los cuales se encuentran en la 
carpeta de componentes, y sus formas de compilacion y uso se encuentran en sus respectivos readme.

*Compilado*
Simplemente se ejecuta make desde la carpeta base del programa asi: $ make
El make ejecutara consecutivamente los make de la carpeta Components y dejara a disposicion el del menu.

*Uso:*
En linux se puede ejecutar asi:
    ./main -u "nombreUsuario" -i "archivo/para/contar.txt" -o "salida/Archivo/contar.txt" -f "archivo/para/crear.txt" -t "textoParaAgregar" -v "n1;n2;...;n4"
El unico argumento obligatorio para iniciar es -u
