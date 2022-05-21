#include "include/ray_tracer.h"
#include "include/dibujar.h"
#include "include/estructuras.h"
#include "include/tipo_figura.h"
#include "include/vector_normal_figura.h"

long double EPSILON=0.0005;

void vertice_interseccion(Interseca * interseccion,Vertice * a, Vertice * d){
    long double nx=(a->x+(interseccion->tmin*d->x)),
                ny=(a->y+(interseccion->tmin*d->y)),
                nz=(a->z+(interseccion->tmin*d->z));
    
    interseccion->interseccion=init_vertice_struct(nx,ny,nz);
}

Interseca * interseccion_esfera(Esfera *esfera, Vertice * origen, Vertice *d)
{
    Interseca * a = malloc(sizeof(Interseca));
    a->tipo=ESFERA;
    a->figura = (void *)esfera;

    long double
        alpha = powl(d->x,2)+powl(d->y,2)+powl(d->z,2),
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

            vertice_interseccion(a,origen,d);
            return a;
        }
        else if(t1>0){
            a->tmin = t1;
            vertice_interseccion(a,origen,d);
            return a;
        }
        else{
            a->tmin = t2;
            vertice_interseccion(a,origen,d);
            return a;
        }
    }

    free(a);
    return NULL;
}

//No estoy muy seguro de si esta funcion puede ser util tomando en cuenta que la distancia minima esta dada por tmin.
long double distancia (Interseca * interseccion, Interseca * temporal)
{
    long double tx = temporal->interseccion->x-interseccion->interseccion->x,
                ty = temporal->interseccion->y-interseccion->interseccion->y,
                tz = temporal->interseccion->z-interseccion->interseccion->z;
    return sqrtl(powl(tx,2)+powl(ty,2)+powl(tz,2));
}

long double intensidad_In (Interseca * interseccion,Vertice * a, Vertice * d){
    long double intensidad=0.0;
    bool ignorar_luz=false;
    Interseca *tmp = NULL;
    Vertice * figura_normal,
            * dir_luz;

    figura_normal = vector_normal_figura(interseccion,interseccion->tipo);
    Foco * iter = lista_focos;

    while(iter != NULL) {
        dir_luz = vector_normal_L(iter,interseccion);
        long double lambert=dir_luz->x*figura_normal->x+
                            dir_luz->y*figura_normal->y+
                            dir_luz->z*figura_normal->z;
        if(lambert>1) lambert=1;
        
        Figura *iter_figuras = lista_figuras;

        if(lambert > 0){
            do
            {
                if (iter_figuras->tipo == ESFERA)
                {
                    tmp = interseccion_esfera((Esfera *)iter_figuras->figura,interseccion->interseccion,dir_luz);
                    
                //Se puede usar tmin en lugar de  dis porque ya deporsi tmin es la distancia minima.
                    if (tmp != NULL && tmp->tmin > EPSILON) {
                        ignorar_luz=true;
                    }
                }
                iter_figuras=iter_figuras->sig;
            } while (iter_figuras != lista_figuras);
        }

        if(!ignorar_luz) {
            intensidad+=(lambert*(iter->intensidad));
            ignorar_luz=false;
        } else {
            ignorar_luz=false;
        }
        iter = iter->sig;
    } 
    return intensidad;
}

//Bueno la verdad es que a esta funcion le encaja mejor el nombre de fist_Interseccion.
Interseca * buscar_Interseccion_Esfera (Vertice * a, Vertice * d)
{
    Figura *iter = lista_figuras;
    Interseca   *interseccion = NULL,
                *tmp = NULL;
    do
    {
        if (iter->tipo == ESFERA)
        {
            tmp = interseccion_esfera((Esfera *)iter->figura,a, d);
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
    return interseccion;
}

Color * de_Que_Color (Interseca * interseccion, Vertice * a, Vertice * d)
{
    if (interseccion == NULL) 
        return init_color_struct (background_color->r,background_color->g,background_color->b);
    
    long double intensidad = intensidad_In (interseccion, a, d);
    if (intensidad==0) intensidad = 0.2;
    if(interseccion->tipo == ESFERA)
        return init_color_struct(((Esfera *) interseccion->figura)->color->r*intensidad,
                                  ((Esfera *) interseccion->figura)->color->g*intensidad,
                                  ((Esfera *) interseccion->figura)->color->b*intensidad);
}

Color * first_intersection (Vertice * a, Vertice * d)
{
    Interseca *interseccion = buscar_Interseccion_Esfera (a, d);
    return de_Que_Color (interseccion, a, d);
}

void ray_tracer()
{
    long double xw, yw, zw, l;
    Vertice *director;
    Color * color;

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

            color=first_intersection(ojo->vertice, director);
            buffer[i][j]=(Color)*color;
            free(color);
        }
        free(director);
    }
}