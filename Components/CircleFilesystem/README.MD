**Sistema de directorio basado en lista circular**
Este programa permite crear directorios basados en una lista circular a partir de un archivo .dre recibe como argumentos la direccion del archivo, el maximo de directorios que puede crear y el maximo de archivos que puede contener cada directorio


*Formato de formato del archivo .dre*
dirbase=./(directorio base)
dirs=(directorios que se vab a crear separados por ";")
(nombre directorio)=(archivos que se van a crear separados por ";")

*Ejemplo de archivo .dre*
dirbase=./salida/
dirs=dir1;dir2;dir3;dir4;dir5
dir1=file1;file2
dir2=file3
dir4=file5;file6;file7;file8

*NOTAS*
Los archivos dentro de los directorios son opcionales
Si solo hay un directorio luego de dirs no se creara un link virtual 
No se crearan directorios no mencionados en dirs, por lo que los archivos que tenga un directorio no mencionado no se crearan

*Descripcion*
- Se reciben los argumentos
- Se lee el archivo .dre
- Se guarda la informacion del archivo en el objeto dirCircle
- Se crean los directorios uno dentro de otro, y el ultimo con un link virtual hacia el primero

*Compilado*
Ejecute make para compilar

*Uso*
En linux se puede ejecutar asi:
    ./main (direccion del archivo .dre) (numero maximo de directiorios) (numero maximo de archivos)
Ej: ./main ../../data/Test.dre 10 10
Todos los argumentos son obligatorios