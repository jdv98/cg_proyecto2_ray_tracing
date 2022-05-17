#include <stdlib.h>
#include <malloc.h>
#include "include/estructuras.h"
#include "include/tipo_figura.h"
#include "include/vector_normal_figura.h"

Vertice * vector_normal_esfera(Interseca * interseccion, Vertice * a, Vertice * d){
    long double nx=(a->x+(interseccion->tmin*d->x)),
                ny=(a->y+(interseccion->tmin*d->y)),
                nz=(a->z+(interseccion->tmin*d->z));

    nx=nx/((Esfera*)interseccion->figura)->radio;
    ny=ny/((Esfera*)interseccion->figura)->radio;
    nz=nz/((Esfera*)interseccion->figura)->radio;

    return init_vertice_struct(nx,ny,nz);
}

Vertice * vector_normal_objetos(void * interseccion, int tipo, Vertice * a, Vertice * d){
    if(tipo == ESFERA){
        return vector_normal_esfera((Interseca*)interseccion,a,d);
    }

    return NULL;
}