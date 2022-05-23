#include <malloc.h>
#include <stdlib.h>
#include "include/estructuras.h"
#include "include/tipo_figura.h"

Foco * lista_focos = NULL;
Figura *lista_figuras = NULL;
Ojo *ojo;
Frame *frame;
Ambiente * ambiente;

long double rango_cero_uno(long double numero){
    if(numero<0)
        return 0;
    else if(numero>1)
        return 1;
    return numero;
}

Color *init_color_struct(double r, double g, double b)
{

    Color *color = malloc(sizeof(Color));

    color->r = r;
    color->g = g;
    color->b = b;

    return color;
}

Vertice *init_vertice_struct(long double x, long double y, long double z)
{

    Vertice *vertice = malloc(sizeof(Vertice));

    vertice->x = x;
    vertice->y = y;
    vertice->z = z;

    return vertice;
}

Foco * init_foco_struct(long double * datos, Vertice * vertice){
    Foco * foco = malloc(sizeof(Foco));

    foco->intensidad=rango_cero_uno(datos[0]);
    foco->c1_f_att=rango_cero_uno(datos[1]);
    foco->c2_f_att=rango_cero_uno(datos[2]);
    foco->c3_f_att=rango_cero_uno(datos[3]);
    free(datos);

    foco->vertice=vertice;

    return foco;
}

void init_ojo_struct(Vertice *vertice)
{
    ojo = malloc(sizeof(Ojo));
    ojo->vertice = vertice;
}

void init_frame_struct(Vertice *bottom_left, Vertice *top_right)
{
    frame = malloc(sizeof(Frame));
    frame->bottom_left = bottom_left;
    frame->top_right = top_right;
}

Cara *init_cara_struct()
{
    Cara *cara = malloc(sizeof(Cara));
    cara->cant_vertices = 0;
    cara->vertices = malloc(0);
    return cara;
}

Esfera *init_esfera_struct(Color *color, long double radio, Vertice *vertice, long double * iluminacion)
{
    Esfera *esfera = malloc(sizeof(Esfera));
    esfera->color = color;

    /***/
    esfera->k_d = iluminacion[0];
    esfera->k_a = iluminacion[1];
    free(iluminacion);
    /***/

    esfera->radio = radio;
    esfera->vertice = vertice;
    return esfera;
}

Poligono *init_poligono_struct(Color *color, long double * iluminacion)
{
    Poligono *poligono = malloc(sizeof(Poligono));
    poligono->cant_caras = 0;
    poligono->caras = malloc(0);
    poligono->color = color;

    /***/
    poligono->k_d = iluminacion[0];
    poligono->k_a = iluminacion[1];
    free(iluminacion);
    /***/

    return poligono;
}

void init_ambiente_struct(long double iluminacion){
    ambiente=malloc(sizeof(Ambiente));

    if(iluminacion<0)
        iluminacion=0;
    else if(iluminacion>1)
        iluminacion=1;

    ambiente->iluminacion=iluminacion;
}

/***/

void ins_vertice_cara(Cara *cara, Vertice *vertice)
{
    cara->cant_vertices++;
    cara->vertices = realloc(cara->vertices, sizeof(Vertice) * cara->cant_vertices);
    cara->vertices[cara->cant_vertices - 1] = vertice;
}

void ins_cara_poligono(Poligono *poligono, Cara *cara)
{
    poligono->cant_caras++;
    poligono->caras = realloc(poligono->caras, sizeof(Cara) * poligono->cant_caras);
    poligono->caras[poligono->cant_caras - 1] = cara;
}

void agregar_figura(void *figura, int tipo_figura)
{
    Figura *figura_nueva = malloc(sizeof(Figura));
    figura_nueva->figura = figura;
    figura_nueva->tipo = tipo_figura;

    figura_nueva->ant = NULL;
    figura_nueva->sig = NULL;

    if (lista_figuras == NULL)
    {
        lista_figuras = figura_nueva;
        figura_nueva->sig=lista_figuras;
    }
    else if (lista_figuras->sig == lista_figuras)
    {
        lista_figuras->sig = figura_nueva;
        lista_figuras->ant = figura_nueva;

        figura_nueva->sig = lista_figuras;
        figura_nueva->ant = lista_figuras;
    }
    else
    {
        Figura *tmp = lista_figuras->ant;
        lista_figuras->ant = figura_nueva;
        tmp->sig = figura_nueva;

        figura_nueva->ant = tmp;
        figura_nueva->sig = lista_figuras;
    }
}

void agregar_foco(Foco * foco){
    if(lista_focos == NULL){
        lista_focos = foco;
        lista_focos->sig = NULL;
    }
    else{
        Foco * iter = lista_focos;
        while (iter->sig != NULL)
        {
            iter = iter->sig;
        }

        iter->sig = foco;
        foco->sig = NULL;
    }
}

/***/

void liberar_esfera(Esfera *esfera)
{
    free(esfera->color);
    free(esfera->vertice);
    free(esfera);
}

void liberar_cara(Cara *cara)
{
    for (size_t i = 0; i < cara->cant_vertices; i++)
    {
        free(cara->vertices[i]);
    }
    free(cara->vertices);
    free(cara);
}

void liberar_poligono(Poligono *poligono)
{
    for (size_t i = 0; i < poligono->cant_caras; i++)
    {
        liberar_cara(poligono->caras[i]);
    }
    free(poligono->caras);
    free(poligono->color);
    free(poligono);
}

void liberar_figura(int posicion)
{
    Figura *iter = lista_figuras;
    int cont = 0;

    do
    {
        if (cont == posicion)
        {
            Figura *ant = iter->ant;
            Figura *sig = iter->sig;

            ant->sig = sig;
            sig->ant = ant;

            if (posicion == 0)
                lista_figuras = sig;

            if (iter->tipo == ESFERA)
                liberar_esfera((Esfera *)iter->figura);
            else if (iter->tipo == POLIGONO)
                liberar_poligono((Poligono *)iter->figura);

            free(iter);
            break;
        }

        iter = iter->sig;
        cont++;
    } while (iter != lista_figuras);
}

void liberar_figuras()
{
    Figura * iter = lista_figuras->sig,
            * tmp;
    do
    {
        if(iter->ant!=NULL && iter->sig!=NULL){
            iter->ant->sig=NULL;
            iter->sig->ant=NULL;
        }
        tmp=iter;
        iter=iter->sig;

        if (tmp->tipo == ESFERA)
            liberar_esfera((Esfera *)tmp->figura);
        else if (tmp->tipo == POLIGONO)
            liberar_poligono((Poligono *)tmp->figura);

    } while (iter != NULL);
}

void liberar_ojo(){
    free(ojo->vertice);
    free(ojo);
}

void liberar_frame(){
    free(frame->bottom_left);
    free(frame->top_right);
    free(frame);
}

/*********************/
/*Obtener informacion*/
/*********************/

long double obtener_kd_figura(void * figura, int tipo) {
    if(tipo==ESFERA){
        return ((Esfera*) figura)->k_d;
    }
    else if(tipo==POLIGONO){
        return ((Poligono*) figura)->k_d;
    }
    return -1;
}

long double obtener_ka_figura(void * figura, int tipo) {
    if(tipo==ESFERA){
        return ((Esfera*) figura)->k_a;
    }
    else if(tipo==POLIGONO){
        return ((Poligono*) figura)->k_a;
    }
    return -1;
}