#ifndef VECTOR_NORMAL_FIGURA_H
#define VECTOR_NORMAL_FIGURA_H

#include "estructuras.h"

Vertice * vector_normal_figura(Interseca * interseccion, int tipo);
Vertice * vector_normal_L(Foco * foco, Interseca * interseccion);
Vertice * vector_normal_v (Vertice * ojo, Interseca * interseccion);

#endif