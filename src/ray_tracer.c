#include "include/ray_tracer.h"
#include "include/dibujar.h"
#include "include/estructuras.h"
#include "include/tipo_figura.h"
#include "include/vector_normal_figura.h"
#include "include/interseccion_objeto.h"
#include <stdio.h>

long double fatt_distancia_luz(Foco * foco, Vertice * a){
    long double distancia = sqrtl(
        powl( a->x - foco->vertice->x , 2 ) +
        powl( a->y - foco->vertice->y , 2 ) +
        powl( a->z - foco->vertice->z , 2 )
    );

    long double f_att=1/(
        foco->c1_f_att +
        foco->c2_f_att * distancia +
        foco->c3_f_att * powl(distancia , 2)
        );

    return f_att > 1 ? 1 : f_att;
}

long double reflexion_difusa (Interseca * interseccion,Vertice * a, Vertice * d){
    long double reflex_difusa=0.0,
                tmax=0;
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

        tmax=(iter->vertice->x - interseccion->interseccion->x)/dir_luz->x;
        
        Figura *iter_figuras = lista_figuras;

        if(lambert > 0 && lambert <= 1){
            do
            {
                if (iter_figuras->tipo == ESFERA)
                {
                    tmp = interseccion_esfera((Esfera *)iter_figuras->figura,interseccion->interseccion,dir_luz);
                }
                else if(iter_figuras->tipo == POLIGONO){
                    tmp = interseccion_poligono((Poligono *)iter_figuras->figura,interseccion->interseccion,dir_luz);
                }

                if (tmp != NULL && tmp->tmin > EPSILON && tmp->tmin<tmax)
                        ignorar_luz=true;
                iter_figuras=iter_figuras->sig;
            } while (iter_figuras != lista_figuras);

            if(!ignorar_luz) {
                reflex_difusa+=
                    (
                        lambert*
                        obtener_kd_figura(interseccion->figura, interseccion->tipo)*
                        (iter->intensidad)*
                        fatt_distancia_luz(iter, interseccion->interseccion)
                    );
            }
            ignorar_luz=false;
        }
        iter = iter->sig;
    } 
    return reflex_difusa;
}

long double reflexion_especular (Interseca * interseccion,Vertice * a, Vertice * d){
    long double reflex_especular = 0.0,
                tmax=0,
                rxl;
    bool ignorar_luz=false;
    Interseca *tmp = NULL;
    Vertice * figura_normal,
            * dir_luz,
            * R,
            * V=init_vertice_struct(-d->x,-d->y,-d->z);

    figura_normal = vector_normal_figura(interseccion,interseccion->tipo);
    Foco * iter = lista_focos;

    while(iter != NULL) {
        dir_luz = vector_normal_L(iter,interseccion);
        long double lambert=dir_luz->x*figura_normal->x+
                            dir_luz->y*figura_normal->y+
                            dir_luz->z*figura_normal->z;

        tmax=(iter->vertice->x - interseccion->interseccion->x)/dir_luz->x;
        
        Figura *iter_figuras = lista_figuras;
        R = vector_R(figura_normal, dir_luz);
        rxl=(R->x*V->x)+(R->y*V->y)+(R->z*V->z);

        if(lambert > 0 && lambert <= 1 && rxl>0.0 && rxl<=1.0){
            do
            {
                if (iter_figuras->tipo == ESFERA)
                {
                    tmp = interseccion_esfera((Esfera *)iter_figuras->figura,interseccion->interseccion,dir_luz);
                }
                else if(iter_figuras->tipo == POLIGONO){
                    tmp = interseccion_poligono((Poligono *)iter_figuras->figura,interseccion->interseccion,dir_luz);
                }
                if (tmp != NULL && tmp->tmin > EPSILON && tmp->tmin<tmax)
                        ignorar_luz=true;

                iter_figuras=iter_figuras->sig;
            } while (iter_figuras != lista_figuras);

            
            if(!ignorar_luz) {
                //reflex_especular += rxl*iter->intensidad*fatt_distancia_luz(iter, interseccion->interseccion);
                reflex_especular += powl(rxl, (long double) obtener_kn_figura(interseccion->figura, interseccion->tipo))*iter->intensidad*fatt_distancia_luz(iter, interseccion->interseccion);
            }
            ignorar_luz=false;
        }
        iter = iter->sig;

        free(R);
    } 
    free(V);
    return reflex_especular;
}

Color * de_que_color (Interseca * interseccion, Vertice * a, Vertice * d)
{
    if (interseccion == NULL) 
        return init_color_struct (background_color->r,background_color->g,background_color->b);

    long double reflex_difusa = reflexion_difusa (interseccion, a, d);
    long double reflex_especular = reflexion_especular (interseccion, a, d);
    
    
    if(reflex_especular>(long double)1)
        reflex_especular=1;
    else if(reflex_especular<(long double)0)
        reflex_especular=0;
    
    reflex_difusa+=(obtener_ka_figura(interseccion->figura, interseccion->tipo)*ambiente->iluminacion);

    if(reflex_difusa>(long double)1)
        reflex_difusa=1;
    else if(reflex_difusa<(long double)0)
        reflex_difusa=0;

    
    if(interseccion->tipo == ESFERA) {
        long double rd=((Esfera *) interseccion->figura)->color->r*reflex_difusa,
                    gd=((Esfera *) interseccion->figura)->color->g*reflex_difusa,
                    bd=((Esfera *) interseccion->figura)->color->b*reflex_difusa;
        return init_color_struct (
                                    rd+( reflex_especular * ( ((long double)1.0) - rd ) ),
                                    gd+( reflex_especular * ( ((long double)1.0) - gd ) ),
                                    bd+( reflex_especular * ( ((long double)1.0) - bd ) )
                                );
    }
    else if(interseccion->tipo == POLIGONO) {
        long double rd=((Poligono *) interseccion->figura)->color->r*reflex_difusa,
                    gd=((Poligono *) interseccion->figura)->color->g*reflex_difusa,
                    bd=((Poligono *) interseccion->figura)->color->b*reflex_difusa;
        return init_color_struct (
                                    rd+( reflex_especular * ( ((long double)1.0) - rd ) ),
                                    gd+( reflex_especular * ( ((long double)1.0) - gd ) ),
                                    bd+( reflex_especular * ( ((long double)1.0) - bd ) )
                                );
    }
}

Color * first_intersection (Vertice * a, Vertice * d)
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
        else if(iter->tipo == POLIGONO){
            tmp = interseccion_poligono((Poligono *)iter->figura,a, d);
        }

        if (tmp != NULL)
        {
            if (interseccion == NULL)
            {
                interseccion = tmp;
            }
            else if (interseccion->tmin > tmp->tmin)
            {
                free(interseccion);
                interseccion = tmp;
            }
            else{
                free(tmp);
            }
        }

        iter=iter->sig;
    } while (iter != lista_figuras);

    return de_que_color (interseccion, a, d);
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
        if((int)(((long double)100/RESOLUCION_W)*i)%10==0){
            system("clear");
            printf("Ray tracer > %i%\n",(int)(((long double)100/RESOLUCION_W)*i));
        }
    }
    {
        system("clear");
        printf("Ray tracer > %i%\n",100);
    }
}