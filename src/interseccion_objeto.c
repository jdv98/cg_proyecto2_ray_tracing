#include "include/estructuras.h"
#include "include/tipo_figura.h"
#include "include/vector_normal_figura.h"
#include "include/interseccion_objeto.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>

void vertice_interseccion(Interseca *interseccion, Vertice *a, Vertice *d)
{
    long double nx = (a->x + (interseccion->tmin * d->x)),
                ny = (a->y + (interseccion->tmin * d->y)),
                nz = (a->z + (interseccion->tmin * d->z));

    interseccion->interseccion = init_vertice_struct(nx, ny, nz);
}

Interseca *interseccion_esfera(Esfera *esfera, Vertice *origen, Vertice *d)
{
    Interseca *a = malloc(sizeof(Interseca));
    a->tipo = ESFERA;
    a->figura = (void *)esfera;

    long double
        alpha = powl(d->x, 2) + powl(d->y, 2) + powl(d->z, 2),
        beta = ((long double)2) * ((d->x * (origen->x - esfera->vertice->x)) +
                                   (d->y * (origen->y - esfera->vertice->y)) +
                                   (d->z * (origen->z - esfera->vertice->z))),
        gamma = powl(origen->x - esfera->vertice->x, 2) +
                powl(origen->y - esfera->vertice->y, 2) +
                powl(origen->z - esfera->vertice->z, 2) -
                powl(esfera->radio, 2),
        t1,
        t2;

    long double tmp = powl(beta, 2) - (4 * alpha * gamma);

    if (tmp == 0)
    {
        t1 = (-beta - sqrtl(tmp)) / (alpha * 2);
        a->tmin = t1;

        return a;
    }
    else if (tmp > 0)
    {
        t1 = (-beta - sqrtl(tmp)) / (2 * alpha);
        t2 = (-beta + sqrtl(tmp)) / (2 * alpha);

        if (t1 > 0 && t2 > 0)
        {
            if (t1 > t2)
                a->tmin = t2;
            else
                a->tmin = t1;

            vertice_interseccion(a, origen, d);
            return a;
        }
        else if (t1 > 0)
        {
            a->tmin = t1;
            vertice_interseccion(a, origen, d);
            return a;
        }
        else if (t2 > 0)
        {
            a->tmin = t2;
            vertice_interseccion(a, origen, d);
            return a;
        }
    }

    free(a);
    return NULL;
}

Interseca * interseccion_poligono(Poligono *poligono, Vertice *origen, Vertice *d)
{
    long double denominador_interseccion = (
                                            powl(d->x * poligono->ecuacion_plano[0], 2) + 
                                            powl(d->y * poligono->ecuacion_plano[1], 2) + 
                                            powl(d->z * poligono->ecuacion_plano[2], 2)
                                            );
    
    if ( denominador_interseccion > 0){
        long double t = -(
                            (origen->x * poligono->ecuacion_plano[0])+
                            (origen->y * poligono->ecuacion_plano[1])+
                            (origen->z * poligono->ecuacion_plano[2])+
                            (poligono->ecuacion_plano[3])
                        )/denominador_interseccion;
        

        Interseca *a = malloc(sizeof(Interseca));
        a->interseccion = init_vertice_struct(
                                    origen->x+(t*d->x),
                                    origen->y+(t*d->y),
                                    origen->z+(t*d->z)
                                );
        a->tmin=t;
        a->tipo=POLIGONO;
        a->figura=(void *) poligono;
        return a;
    }
    return NULL;
}