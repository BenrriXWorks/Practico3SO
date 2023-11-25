#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <vector>
#include <algorithm>
#include <execution>

#define GRAPH_SIZE 100
#define WINDOW_SIZE 500
#define PADDING 20
#define SCR_BOTTOM_AXIS_X (WINDOW_SIZE - PADDING)
#define SCR_BOTTOM_AXIS_Y (WINDOW_SIZE - PADDING)

// Regla de 3 para transformar los puntos del grafico
std::pair<float, float> transformPoint(std::pair<unsigned char, unsigned char> point, unsigned int axisLength, unsigned int graphSize, unsigned int padding){
    return std::pair<float, float> (point.first*axisLength/100 + padding, (graphSize - point.second)*axisLength/100 - padding);
}

int main(){

    // Colocar el titulo del grafico por ponerlo
    char titulo[512]{};
    strcpy(titulo, "El graficador de Benrrix");

    // Leer los puntos
    std::vector<std::pair<unsigned char, unsigned char>> points {{1,5},{3,6},{4,8},{10,9},{32,15},{50,50}};
    // Transformar los puntos a coordenadas de pantalla
    auto pointsComparator = [](std::pair<unsigned char, unsigned char> p1, std::pair<unsigned char, unsigned char> p2){ return p1.first < p2.first; };
    sort(std::execution::par, points.begin(), points.end(), pointsComparator);

    // Iniciar el display
    Display *display = XOpenDisplay(nullptr);
    if (display == nullptr) {
        fputs_unlocked("No se pudo crear la pantalla\n", stdout);
        return EXIT_FAILURE;
    }
    
    // Crear la pantalla 'drawable'
    int screen = DefaultScreen(display);
    GC gc = DefaultGC(display, screen);

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
    

    // Enlazar el display a la ventana
    XSelectInput(display, window, ExposureMask | KeyPressMask);
    XMapWindow(display, window);

    // Tamano minimo de la pantalla
    XSizeHints windowSizeHint;
    windowSizeHint.flags = PMinSize | PMaxSize;
    windowSizeHint.min_width = WINDOW_SIZE;
    windowSizeHint.min_height = WINDOW_SIZE;
    windowSizeHint.max_height = WINDOW_SIZE;
    XSetWMNormalHints(display, window, &windowSizeHint);

    for (;;){

        // Leer los eventos (Iniciar o presionar una tecla para cerrar)
        XEvent event;
        XNextEvent(display, &event);

        if (event.type == KeyPress){
            break;
        }

        // Si la ventana carga por primera vez, se colocan los puntos en el display
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
                XDrawLine(display, window, gc, i, SCR_BOTTOM_AXIS_Y + PADDING/4, i, SCR_BOTTOM_AXIS_Y - PADDING/4);
                XDrawString(display, window, gc, i - 4, SCR_BOTTOM_AXIS_Y + PADDING - 2, lineLabel, strlen(lineLabel));
                // Lineas superiores
                XDrawLine(display, window, gc, PADDING/4, SCR_BOTTOM_AXIS_Y + PADDING - i, PADDING*1.25f, SCR_BOTTOM_AXIS_Y + PADDING - i);
                XDrawString(display, window, gc, PADDING/2 - 4, SCR_BOTTOM_AXIS_Y + PADDING - i, lineLabel, strlen(lineLabel));
            
            }

            // Dibujar los puntos
            if (points.size() == 1)
                return(fputs_unlocked("No puedes hacer un grafico de lineas con un punto :(\n",stdout),EXIT_FAILURE);
            else {

                // Por cada par de puntos, hacer una linea
                auto last = points.front();
                for (size_t i = 1; i < points.size(); ++i){
                    
                    // Colocar el label sobre los puntos
                    auto p = points[i];
                    char label[50]{};
                    sprintf(label, "(%d, %d)", p.first, p.second);
                    
                    // Transformar los puntos a coordenadas de pantalla
                    auto newScrPoint = transformPoint(p, SCR_BOTTOM_AXIS_X, GRAPH_SIZE, PADDING);
                    auto lastScrPoint = transformPoint(last, SCR_BOTTOM_AXIS_X, GRAPH_SIZE, PADDING);
                    printf("Transformed point: %f, %f\n", newScrPoint.first, newScrPoint.second);
                    
                    // Dibujar las lineas entre puntos en pantalla
                    XDrawLine(display, window, gc, lastScrPoint.first, lastScrPoint.second, newScrPoint.first, newScrPoint.second);
                    //XDrawString(display, window, gc, newScrPoint.first, newScrPoint.second, label, strlen(label));

                    // Cambiar registro del ultimo elemento
                    last = p;
                }

            }
        }
    }

    return EXIT_SUCCESS;
}