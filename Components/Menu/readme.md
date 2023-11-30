**Aplicacion de menu con inicio de sesion y funciones**
Esta aplicacion permite realizar un login y cargar un menu con
funciones dependientes de los permisos del usuario.
Esta aplicacion contiene los siguientes componentes:
- Login, Menu, Indexer & IndexInverter.

*Descripcion:*
- Se leen los argumentos del archivo .env
- Se inicia sesion con el modulo de login y se recibe un token encriptado.
- Se lee la respuesta y se crea el usuario.
- Se inicia un menu con las opciones disponibles.

*Configuracion:*
- Se puede modificar el programa con:
- .env (para las rutas y variables) respetando el formato estandar de un archivo ENV.
- data/Options.txt: Cambiar las opciones del menu {n_opcion,texto_opcion,funcion_opcion}
    ej: 0,Salir del programa,salir
- data/Permissions.txt: Cambiar los permisos por tipo de perfil {tipo;n_permisos}, si n_permisos=* entonces son todos, no se incluye el permiso 0.
    ej: rookie;1,2,3
- data/Users.txt: Agregar usuarios {nombre,perfil}
    ej: benjamin,admin

*Compilado*
Simplemente se ejecuta make desde la carpeta base del programa asi: $ make

*Uso:*
Al compilar este archivo, se creara el ejecutable dos carpetas atras, por lo que se debe volver a la 
carpeta base, luego, desde ahi, en linux se puede ejecutar asi:
    ./main -u "nombreUsuario" -i "archivo/para/contar.txt" -o "salida/Archivo/contar.txt" -f "archivo/para/crear.txt" -t "textoParaAgregar" -v "n1;n2;...;n4"