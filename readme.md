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
INDEXER_PATH, LOGIN_EXECUTABLE, INVERTED_INDEXER_PATH, TOPK}.
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
