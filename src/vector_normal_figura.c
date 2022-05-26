#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include "include/estructuras.h"
#include "include/tipo_figura.h"
#include "include/vector_normal_figura.h"

Vertice * vector_normal_esfera(Interseca * interseccion){
    long double nx=(interseccion->interseccion->x-(((Esfera*)interseccion->figura)->vertice->x))/((Esfera*)interseccion->figura)->radio,
                ny=(interseccion->interseccion->y-(((Esfera*)interseccion->figura)->vertice->y))/((Esfera*)interseccion->figura)->radio,
                nz=(interseccion->interseccion->z-(((Esfera*)interseccion->figura)->vertice->z))/((Esfera*)interseccion->figura)->radio;

    return init_vertice_struct(nx,ny,nz);
}

Vertice * vector_normal_figura(Interseca * interseccion, int tipo){
    if(tipo == ESFERA){
        return vector_normal_esfera((Interseca*)interseccion);
    }

    return NULL;
}

Vertice * vector_normal_L(Foco * foco, Interseca * interseccion){
    long double nx=foco->vertice->x-(interseccion->interseccion->x),
                ny=foco->vertice->y-(interseccion->interseccion->y),
                nz=foco->vertice->z-(interseccion->interseccion->z);

    long double dis=sqrtl(powl(nx,2)+powl(ny,2)+powl(nz,2));

    return init_vertice_struct(nx/dis,ny/dis,nz/dis);
}

Vertice * vector_normal_v (Vertice * ojo, Interseca * interseccion) {
    long double nx=ojo->x-(interseccion->interseccion->x),
                ny=ojo->y-(interseccion->interseccion->y),
                nz=ojo->z-(interseccion->interseccion->z);

    long double dis=sqrtl(powl(nx,2)+powl(ny,2)+powl(nz,2));

    return init_vertice_struct(nx/dis,ny/dis,nz/dis);
}