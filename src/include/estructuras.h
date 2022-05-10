#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

/**********************************/

typedef struct Vertice Vertice;
typedef struct Cara Cara;
typedef struct Esfera Esfera;
typedef struct Poligono Poligono;
typedef struct Figura Figura;
typedef struct Frame Frame;
typedef struct Ojo Ojo;
typedef struct Color Color;

/**********************************/

struct Vertice {
    long double x,y,z;
};

struct Cara
{
    int cant_vertices;
    Vertice * * vertices;
};

struct Esfera{
    Color * color;
    Vertice * vertice;
    long double radio;
};

struct Poligono{
    Color * color;
    int cant_caras;
    Cara * * caras;
};

struct Figura
{
    int tipo;
    void * figura;
    Figura * sig;
    Figura * ant;
};

struct Ojo
{
    Vertice * vertice;
};

struct Frame
{
    Vertice * bottom_left;
    Vertice * top_right;
};

struct Color{
    double r;
    double g;
    double b;
};

/**********************************/

extern Figura * lista_figuras;
extern Ojo * ojo;
extern Frame * frame;

/**********************************/


Color * init_color_struct(double r,double g,double b);
Vertice * init_vertice_struct(long double x,long double y,long double z);
void init_ojo_struct(Vertice * vertice);
void init_frame_struct(Vertice * bottom_left,Vertice * top_right);
Cara * init_cara_struct();
Esfera * init_esfera_struct(Color * color, long double radio, Vertice * vertice);
Poligono * init_poligono_struct(Color * color);


void ins_vertice_cara(Cara * cara, Vertice * vertice);
void ins_cara_poligono(Poligono * poligono, Cara * cara);
void agregar_figura( void * figura, int tipo_figura);


void liberar_esfera(Esfera *esfera);
void liberar_cara(Cara *cara);
void liberar_poligono(Poligono *poligono);
void liberar_figura(int posicion);
void liberar_figuras();
void liberar_ojo();
void liberar_frame();
#endif