# Titulo
Graficador 100x100 con X11.

# Descripcion
- Se lee un archivo .gra indicado en la llamada
- Se leen las variables de entorno PADDING y WINDOW_SIZE, del proceso o del .env si no existe.
- Se crea un grafico de lineas con los puntos del archivo leido con los puntos [(x,y) | x <- [0..100f], y<-[0..100f]] 
- Se cierra el grafico al presionar alguna tecla sobre el, luego se termina la ejecucion.

# Entrada
Formato archivo .gra:
    titulo={Titulo}
    x={x1},y={y1}
    x={x2},y={y2}
    ...
Ejemplo archivo .gra:
    titulo:"grafico de linea"
    x:10,y:9
    x:32,y:15
    x:50,y:50
    x:100,y:100
Nota 1: Si el titulo lleva comillas, el programa las saltara al imprimirlo.
Nota 2: El dominio de los puntos debe estar entre [0-100]x[0-100]
Nota 3: El orden siempre es x:{},y:{}
Nota 4: Se puede colocar titulo vacio si se hace "" o no se coloca nada luego del :

# Variables de entorno
    WINDOW_SIZE: Tamano de la ventana
    PADDING: Tamano del padding, el margen seguro es [30-100]


# Compilacion
    Usar el make de la carpeta mas externa, en bash: $ make
    
# Uso:
    Estructura bash: $ ./main {ruta/archivo/puntos}.gra
    Ej: $ ./main "../../data/points.gra"
