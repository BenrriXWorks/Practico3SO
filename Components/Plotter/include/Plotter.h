#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <vector>
#include <algorithm>
#include <execution>



/*
Funcion de graficado.
points: vector de pares x,y a graficar, dom = [x | x->Z, 0<=x<=512]

Debe tener indicado por entorno antes:
    "WINDOW_SIZE",
    "PADDING"
*/
int plot(std::vector<std::pair<float, float>> points, const char* tituloGrafico);

// Funcion de transformacion de puntos de entrada a puntos de pantalla
std::pair<float, float> transformPoint(std::pair<float, float> point, unsigned int axisLength, unsigned int graphSize, unsigned int padding);