#ifndef INTERSECCION_OBJETO_H
#define INTERSECCION_OBJETO_H

#include "estructuras.h"

void vertice_interseccion(Interseca * interseccion,Vertice * a, Vertice * d);
Interseca * interseccion_esfera(Esfera *esfera, Vertice * origen, Vertice *d);
Interseca * interseccion_poligono(Poligono * poligono, Vertice * origen, Vertice *d);

#endif