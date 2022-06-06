#include "include/estructuras.h"
#include "include/tipo_figura.h"
#include "include/vector_normal_figura.h"
#include "include/interseccion_objeto.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <stdbool.h>

int interseccion_u_pos(long double ax1, long double ay1, long double ax2, long double ay2,
                        long double bx1, long double by1, long double bx2, long double by2)
{
    long double a1 = ay2 - ay1,
                b1 = ax1 - ax2,
                a2 = by2 - by1,
                b2 = bx1 - bx2;
    
    long double c1 = a1*(ax1) + b1*(ay1),
                c2 = a2*(bx1)+ b2*(by1);

    long double deter = a1*b2 - a2*b1;

    if(deter>EPSILON || deter<-EPSILON)
    {
        long double u = (b2*c1 - b1*c2)/deter;

        if(u>=0){
            return 1;
        }
    }
    return 0;
}

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

        vertice_interseccion(a, origen, d);
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

void convertir_poligono_a_2d(Poligono *poligono, Vertice *interseccion, long double ***lista_vertices)
{
    (*lista_vertices) = (long double **) calloc((poligono->cant_vertices  ),sizeof(long double) );

    int estado = -1;

    long double
        a = poligono->ecuacion_plano[0] >= (long double)0 ? poligono->ecuacion_plano[0] : -poligono->ecuacion_plano[0],
        b = poligono->ecuacion_plano[1] >= (long double)0 ? poligono->ecuacion_plano[1] : -poligono->ecuacion_plano[1],
        c = poligono->ecuacion_plano[2] >= (long double)0 ? poligono->ecuacion_plano[2] : -poligono->ecuacion_plano[2];

    (*lista_vertices)[0] = (long double *)malloc(sizeof(long double) * 2);
    (*lista_vertices)[poligono->cant_vertices] = (long double *)malloc(sizeof(long double) * 2);

    if (a > b && a > c)
    {
        estado = 0;

        (*lista_vertices)[0][0] = poligono->vertices[0]->y - interseccion->y;
        (*lista_vertices)[0][1] = poligono->vertices[0]->z - interseccion->z;

        (*lista_vertices)[poligono->cant_vertices][0] = (*lista_vertices)[0][0];
        (*lista_vertices)[poligono->cant_vertices][1] = (*lista_vertices)[0][1];
    }
    else if (b > a && b > c)
    {
        estado = 1;

        (*lista_vertices)[0][0] = poligono->vertices[0]->x - interseccion->x;
        (*lista_vertices)[0][1] = poligono->vertices[0]->z - interseccion->z;

        (*lista_vertices)[poligono->cant_vertices][0] = (*lista_vertices)[0][0];
        (*lista_vertices)[poligono->cant_vertices][1] = (*lista_vertices)[0][1];
    }
    else
    {
        estado = 2;

        (*lista_vertices)[0][0] = poligono->vertices[0]->x - interseccion->x;
        (*lista_vertices)[0][1] = poligono->vertices[0]->y - interseccion->y;

        (*lista_vertices)[poligono->cant_vertices][0] = (*lista_vertices)[0][0];
        (*lista_vertices)[poligono->cant_vertices][1] = (*lista_vertices)[0][1];
    }

    for (size_t i = 1; i < poligono->cant_vertices; i++)
    {
        (*lista_vertices)[i] = (long double *)malloc(sizeof(long double) * 2);

        if (estado == 0)
        {
            (*lista_vertices)[i][0] = poligono->vertices[i]->y - interseccion->y;
            (*lista_vertices)[i][1] = poligono->vertices[i]->z - interseccion->z;
        }
        else if (estado == 1)
        {
            (*lista_vertices)[i][0] = poligono->vertices[i]->x - interseccion->x;
            (*lista_vertices)[i][1] = poligono->vertices[i]->z - interseccion->z;
        }
        else if (estado == 2)
        {
            (*lista_vertices)[i][0] = poligono->vertices[i]->x - interseccion->x;
            (*lista_vertices)[i][1] = poligono->vertices[i]->y - interseccion->y;
        }
    }
}

bool interseccion_poligono_a_2d(Poligono *poligono, Vertice *interseccion)
{
    long double **n_poligono;
    convertir_poligono_a_2d(poligono, interseccion, &n_poligono);

    int cont = 0;

    for (size_t i = 0; i < poligono->cant_vertices; i++)
    {
        
        if (!( (n_poligono[i][1] > 0 && n_poligono[i + 1][1] > 0) || (n_poligono[i][1] < 0 && n_poligono[i + 1][1] < 0) ))
        {
            if ( n_poligono[i][0] > 0 && n_poligono[i + 1][0] > 0 )
            {
                if(n_poligono[i + 1][1] == 0)
                    i++;

                cont++;
            }
            else if ( !( (n_poligono[i][0] > EPSILON && n_poligono[i + 1][0] > EPSILON) || (n_poligono[i][0] < -EPSILON && n_poligono[i + 1][0] < -EPSILON) ) ){
                long double u= n_poligono[i][0]>n_poligono[i + 1][0]?n_poligono[i][0]:n_poligono[i + 1][0];

                if(interseccion_u_pos((long double)-0.0, (long double)-0.0, u+(long double)1000, (long double)-0.0, n_poligono[i][0], n_poligono[i][1], n_poligono[i + 1][0], n_poligono[i + 1][1])){
                    if(n_poligono[i + 1][1] == 0)
                        i++;

                    cont++;
                }
            }
            
        }
        free(n_poligono[i]);
    }
    free(n_poligono[poligono->cant_vertices]);
    free(n_poligono);

    return cont % 2;
}

Interseca *interseccion_poligono(Poligono *poligono, Vertice *origen, Vertice *d)
{
    long double denominador_interseccion = (d->x * poligono->ecuacion_plano[0]) +
                                            (d->y * poligono->ecuacion_plano[1]) +
                                            (d->z * poligono->ecuacion_plano[2]);

    if (denominador_interseccion != (long double)0.0)
    {
        long double t = -(
                            (origen->x * poligono->ecuacion_plano[0]) +
                            (origen->y * poligono->ecuacion_plano[1]) +
                            (origen->z * poligono->ecuacion_plano[2]) +
                            (poligono->ecuacion_plano[3])) /
                        denominador_interseccion;

        Vertice *interseccion = init_vertice_struct(
            origen->x + (t * d->x),
            origen->y + (t * d->y),
            origen->z + (t * d->z));

        if (interseccion_poligono_a_2d(poligono, interseccion))
        {
            Interseca *a = malloc(sizeof(Interseca));
            a->interseccion = interseccion;
            a->tmin = t;
            a->tipo = POLIGONO;
            a->figura = (void *)poligono;
            return a;
        }

        free(interseccion);
    }
    return NULL;
}