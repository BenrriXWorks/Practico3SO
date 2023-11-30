**Aplicacion de busqueda de index**
Lee un archivo de index invertido de la forma:
palabra:(nombreArchivo,cantidad);(nombreArchivo,cantidad)
palabra:(nombreArchivo,cantidad)
...
Ej:
frotaras:(file019.txt,1);(file005.txt,1);(file015.txt,1)
impliques:(file003.txt,1)
bicicleta:(file007.txt,1);(file008.txt,1)

Permite saber que archivos (los K con mas coincidencias)
contienen ciertas palabras las cuales se le preguntan al
usuario a través de un menu en consola al ejecutarlo.


*Uso*
El programa debe llamarse:
$ ./main ruta/index TopK
donde topk es la cantidad de resultados a mostrar en pantalla, y
debe ser un numero mayor a 4.
Ej: $ ./main index.idx 5

*compilacion*
Basta con usar $ make
