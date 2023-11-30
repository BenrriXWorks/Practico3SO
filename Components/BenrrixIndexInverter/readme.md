**Aplicacion de indexacion inversa**
Lee archivos de la forma:
palabra,cantidad
palabra,cantidad

por ejemplo:
destrozar,2
sobresaltando,1
clavar,4
y genera un indice invertido con todos los elementos de la carpeta.

*Uso*
El programa debe llamarse ./main "/ruta/archivo/index.idx" "/ruta/archivos/procesados"
por ejemplo:
    ./main output/index.idx input

*compilacion*
basta con usar $ make

*Salida*
En STDOUT se escriben mensajes de informe del proceso.
El archivo idx es de la siguiente forma por linea:
palabra:(archivo,veces);(archivo,veces)...(archivo,veces)

Ej:
adopten:(file002.txt,1)
texacto:(file022.txt,1)
prospera:(file007.txt,2);(file006.txt,1);(file016.txt,1)