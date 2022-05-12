#include "include/ray_tracer.h"
#include "include/dibujar.h"
#include "include/estructuras.h"
#include "include/tipo_figura.h"

typedef struct Interseca
{
    long double tmin;
    int tipo;
    void * figura;
} Interseca;

Interseca * interseccion_esfera(Esfera *esfera, Vertice *d)
{
    Interseca * a = malloc(sizeof(Interseca));
    a->tipo=ESFERA;
    a->figura = (void *)esfera;

    long double
        alpha = powl(d->x,2)+powl(d->y,2)+powl(d->z,2),
        beta = ((long double)2) * ((d->x * (ojo->vertice->x - esfera->vertice->x)) +
                                   (d->y * (ojo->vertice->y - esfera->vertice->y)) +
                                   (d->z * (ojo->vertice->z - esfera->vertice->z))),
        gamma = powl(ojo->vertice->x - esfera->vertice->x, 2) +
                powl(ojo->vertice->y - esfera->vertice->y, 2) +
                powl(ojo->vertice->z - esfera->vertice->z, 2) -
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
            return a;
        }
        else if(t1>0){
            a->tmin = t1;
            return a;
        }
        else{
            a->tmin = t2;
            return a;
        }
    }

    free(a);
    return NULL;
}

Color * first_intersection(Vertice * a, Vertice * d)
{
    Figura *iter = lista_figuras;
    Interseca *interseccion = NULL,
              *tmp = NULL;

    do
    {
        if (iter->tipo == ESFERA)
        {
            tmp = interseccion_esfera((Esfera *)iter->figura, d);
        }

        if (tmp != NULL)
        {
            if (interseccion == NULL)
            {
                interseccion = tmp;
            }
            else if (interseccion->tmin > tmp->tmin)
            {
                interseccion = tmp;
            }
        }

        iter=iter->sig;
    } while (iter != lista_figuras);

    if(interseccion!=NULL)
        if(interseccion->tipo==ESFERA)
            return ((Esfera *) interseccion->figura)->color;
    return background_color;
}

void ray_tracer()
{
    long double xw, yw, zw, l;
    Vertice *director;

    for (int i = 0; i < RESOLUCION_W; i++)
    {
        for (int j = 0; j < RESOLUCION_H; j++)
        {

            xw = ((i + 0.5) * (frame->top_right->x - frame->bottom_left->x)) / RESOLUCION_W + frame->bottom_left->x;
            yw = ((j + 0.5) * (frame->top_right->y - frame->bottom_left->y)) / RESOLUCION_H + frame->bottom_left->y;
            zw = 0;

            l = sqrtl(
                powl((xw - ojo->vertice->x), 2) +
                powl((yw - ojo->vertice->y), 2) +
                powl((zw - ojo->vertice->z), 2)
                );

            director = init_vertice_struct(
                (xw - ojo->vertice->x) / l,
                (yw - ojo->vertice->y) / l,
                (zw - ojo->vertice->z) / l);

            buffer[i][j]=(Color)*first_intersection(ojo->vertice, director);
        }
        free(director);
    }
}