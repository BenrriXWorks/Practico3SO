**Aplicacion de indexacion de texto por carpetas**
Esta aplicacion lee todos los archivos de una carpeta que se llamen
file[0-9]+.txt, por ejemplo file001.txt, y usando threads cuenta todas las palabras distintas
y las veces que aparecen en los textos, luego, por cada uno, se crea un archivo
de salida file001.txt.
Se crea un cache para limpiar los archivos con normalizaTexto.py archivo1.txt, archivo2.txt ...
en processed/ de manera que se usan esos archivos para la indexacion.
La salida queda en una ruta especificada por el usuario.

*compilacion*
Simplemente basta con usar $ make

*Uso*
Para usar esta aplicacion, debe llamarse indicando los siguientes argumentos:
./main EXTENTION PATH_FILES_IN PATH_FILES_OUT AMOUNT_THREADS
    Por ejemplo:
        $ ./main txt input output 8
de manera que solo se leen archivos en PATH_FILES_IN, que tengan la extension EXTENTION,
luego se guardan en la carpeta PATH_FILES_OUT procesando con AMOUNT_THREADS threads.
Se puede definir la variable de entorno AT_LEAST_20_FILES_INDEX opcionalmente, de manera que si
es igual a 1 o la variable no esta definida, deben haber al menos 20 archivos, sino, pueden ser
menos.

*Salida*
En stdout se escribira como avanza el proceso, y se generara un archivo de salida en
PATH_FILES_OUT que contiene separado por saltos de linea {palabra,cantidad}, por ejemplo:
llanguida,1
dentro,11
cono,2
...

