#include "../../include/Plotter.h"

#define GRAPH_SIZE 100
#define WINDOW_SIZE atoi(getenv("WINDOW_SIZE"))
#define PADDING atoi(getenv("PADDING"))
#define SCR_BOTTOM_AXIS_X (WINDOW_SIZE - PADDING)
#define SCR_BOTTOM_AXIS_Y (WINDOW_SIZE - PADDING)

// Regla de 3 + desplazamiento de padding para transformar los puntos del grafico
std::pair<float, float> transformPoint(std::pair<float, float> point, unsigned int axisLength, unsigned int graphSize, unsigned int padding){
    return std::pair<float, float> (point.first*(axisLength - padding)/100 + padding, (graphSize - point.second)*(axisLength - padding)/100 + padding);
}

/*
Funcion de graficado.
points: vector de pares x,y a graficar, dom = [x | x->Z, 0<=x<=512]

Debe tener indicado por entorno antes:
    "WINDOW_SIZE",
    "PADDING"
*/
int plot(std::vector<std::pair<float, float>> points, const char* titulo){


    // Iniciar el display
    Display *display = XOpenDisplay(nullptr);
    if (display == nullptr) 
        return(fputs_unlocked("No se pudo crear la pantalla\n", stdout), EXIT_FAILURE);
    
    // Crear la pantalla 'drawable'
    int screen = DefaultScreen(display);

    // Iniciar la ventana 
    Window window = XCreateSimpleWindow(
        display, 
        RootWindow(display, screen),
        GRAPH_SIZE, GRAPH_SIZE,
        WINDOW_SIZE, WINDOW_SIZE,
        1,
        BlackPixel(display, screen),
        WhitePixel(display,screen)
    ); 

    // Esquemas de pintado
    GC gc = DefaultGC(display, screen);
    GC redGC = XCreateGC(display, window, 0, nullptr);
    XSetForeground(display, redGC, 0xFF0000); // GC rojo para los cuadrados
    

    // Enlazar el display a la ventana
    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);

    // Tamano fijo de la pantalla como un hint
    XSizeHints windowSizeHint;
    windowSizeHint.flags = PMinSize | PMaxSize;
    windowSizeHint.min_width = WINDOW_SIZE;
    windowSizeHint.max_width = WINDOW_SIZE;
    windowSizeHint.min_height = WINDOW_SIZE;
    windowSizeHint.max_height = WINDOW_SIZE;
    XSetWMNormalHints(display, window, &windowSizeHint);


    // Colocar un tituloa a la ventana (no al grafico)
    XStoreName(display, window, titulo);

    // Se convierte la senal de cierre con la x en un mensaje, ya no cierra la ventana.
    Atom wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", false);
    XSetWMProtocols(display, window, &wmDeleteMessage, 1);

    // Loop de inicio (Por si se quieren modificar los eventos mas adelante)
    fputs_unlocked("Presione cualquier tecla sobre el grafico para cerrarlo\n", stdout);
    for (;;){

        // Leer los eventos de la ventana
        XEvent event;
        XNextEvent(display, &event);

        // Cerrar la pantalla si se presiona una tecla (como R)
        if (event.type == KeyPress) break;

        // Cuando la ventana se vuelve visible
        if (event.type == Expose){

            // Titulo del grafico
            XDrawString(display, window, gc, WINDOW_SIZE/2 - strlen(titulo)*2, PADDING, titulo, strlen(titulo));

            // Colocar los ejes
            XDrawLine(display, window, gc, PADDING, SCR_BOTTOM_AXIS_X, SCR_BOTTOM_AXIS_X, SCR_BOTTOM_AXIS_X);
            XDrawLine(display, window, gc, PADDING, PADDING, PADDING, SCR_BOTTOM_AXIS_Y);

            // Dibujar las lineas indicadoras y los strings labels
            int diezPorciento = (SCR_BOTTOM_AXIS_X - PADDING)/10;
            for (int i = diezPorciento + PADDING; i < SCR_BOTTOM_AXIS_X + 1; i += diezPorciento){
                // Label de las lineas:
                char* lineLabel = new char[4] {};
                sprintf(lineLabel, "%d", (i-PADDING)/diezPorciento*10);
                // Lineas inferiores
                XDrawLine(display, window, gc, i, SCR_BOTTOM_AXIS_Y + PADDING/4, i, SCR_BOTTOM_AXIS_Y);
                XDrawString(display, window, gc, i - 4, SCR_BOTTOM_AXIS_Y + PADDING/2, lineLabel, strlen(lineLabel));
                // Lineas superiores
                XDrawLine(display, window, gc, PADDING - 20, SCR_BOTTOM_AXIS_Y + PADDING - i, PADDING, SCR_BOTTOM_AXIS_Y + PADDING - i);
                XDrawString(display, window, gc, PADDING - 25, SCR_BOTTOM_AXIS_Y + PADDING - i, lineLabel, strlen(lineLabel));
            
            }

            // Dibujar los puntos
            // Por cada par de puntos, hacer una linea
            auto last = points.front();
            // Hacer el primer puntito en pantalla
            auto firstPoint = transformPoint(last, SCR_BOTTOM_AXIS_X, GRAPH_SIZE, PADDING);
            XDrawRectangle(display, window, redGC, firstPoint.first-2, firstPoint.second-2, 4, 4);
            for (size_t i = 1; i < points.size(); ++i){
                
                // Colocar el label sobre los puntos
                auto p = points[i];
                char label[50]{};
                sprintf(label, "(%f, %f)", p.first, p.second);
                
                // Transformar los puntos a coordenadas de pantalla
                auto newScrPoint = transformPoint(p, SCR_BOTTOM_AXIS_X, GRAPH_SIZE, PADDING);
                auto lastScrPoint = transformPoint(last, SCR_BOTTOM_AXIS_X, GRAPH_SIZE, PADDING);
                
                // Dibujar las lineas entre puntos en pantalla
                XDrawLine(display, window, gc, lastScrPoint.first, lastScrPoint.second, newScrPoint.first, newScrPoint.second);
                XDrawRectangle(display, window, redGC, newScrPoint.first - 2, newScrPoint.second - 2, 4, 4);
                //XDrawString(display, window, gc, newScrPoint.first, newScrPoint.second, label, strlen(label));

                // Cambiar registro del ultimo elemento
                last = p;
            

            }
        }
    }

    XCloseDisplay(display);
    printf("Saliendo!\n");
    return EXIT_SUCCESS;
}