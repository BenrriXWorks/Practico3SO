# Titulo
TreeFilesystem

# Descripcion
Creador de carpetas basado en arboles con JSON con un archivo .dit
Se crean las carpetas y archivos desde el dirBase recursivamente asignando los permisos especificados.

# Entrada
Argumentos: 
    [1]: Ruta del archivo .dit

# Formato de archivos a leer
.dit:
    Debe ser un objeto json que tenga dirBase, que no exista, y el campo objetos.
    En los objetos pueden haber dos tipos:
        Archivos, que tienen tipo, nombre, contenido y un arreglo con permisos en cualquier combinacion entre ["escritura","lectura"]
        Nota: Si no se colocan los permisos por defecto rw; Nunca se otorga el permio -x actualmente.
            Ej: {"tipo":"archivo","nombre":"file180","contenido":"la la","permisos":["escritura"]}
        Directorios, que tienen tipo, nombre y los objetos que contiene
            Ej: {"tipo":"directorio","nombre":"dir1", "objetos":[]}
    Ejemplo completo:
    {
    "dirBase":"./testfolder",
    "objetos":[
        {"tipo":"archivo","nombre":"randomFile","contenido":"", "permisos":[]},
        {"tipo":"directorio","nombre":"dir1", "objetos":[
            {"tipo":"archivo","nombre":"file1","contenido":"la la","permisos":["escritura","lectura"]}
        ]}
    ]}
    Si algun archivo o directorio no cumple el formato de alguna manera, se saltara.


# Compilacion
Solo hay que ejecutar el make
Ej bash: $ make


# Uso
Solo se pide el argumento de la ruta del archivo .dit
Ejemplo bash: $ ./main "../../data/Test.dit"

# External:
Se usa la libreria de json de nlohmann, link de repo: https://github.com/nlohmann/json
Se necesita tener tree instalado si se quiere desplegar los resultados correctamente