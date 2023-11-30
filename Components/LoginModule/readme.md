**Aplicacion de inicio de sesion**
Esta aplicacion permite emitir una respuesta en la consola revisando
en una base de datos de texto si un usuario existe. Si la respuesta
es positiva, se encripta.

*formato base de datos*
Permisos: {tipoPerfil;permiso1,permiso2,....,permison}
    Ej: general;1,2,3,4,5
Usuarios: {nombreUsuario,tipoPerfil}
    Ej: benjamin,admin

*compilar*
Simplemente puedes usar $ make

*Ejecucion* 
Tras compilar, desde linux se puede ejecutar con este comando:
./main {nombreUsuario} {pathUsuarios} {pathPermisos}

*Salida - precaucion*
El token viene encriptado de la siguiente manera
success:n-token
    Ej: Success:1-admi`lhm`clhm07335633/626/8440504
Si sumas n (en este caso 1) al ascii de todo lo del lado derecho del guion, queda:
benjamin admin 18446744073709551615
El numero (2^64-1) de la derecha son los permisos en binario (de derecha a izquierda)
donde 1 indica que lo tiene y 0 que no.
Si el programa devuelve otra cosa, significa que el inicio de sesion fue incorrecto, asi
que se debe revisar por el Success: al comienzo del mensaje para hacer la distincion.
