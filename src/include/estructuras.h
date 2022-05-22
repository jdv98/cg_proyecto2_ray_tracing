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
typedef struct Foco Foco;
typedef struct Ambiente Ambiente;

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
    Vertice * k_d; //Coeficiente de reflexion difusa
    long double k_a; //Coeficiente de iluminacion ambiente
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
    //long double k_d; //Coeficiente de reflexion difusa
    //long double k_a; //Coeficiente de iluminacion ambiente
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

struct Foco
{
    long double intensidad;
    Vertice * vertice;
    Foco * sig;
};

struct Ambiente
{
    long double iluminacion;
};

typedef struct Interseca
{
    long double tmin;
    Vertice * interseccion; 
    int tipo;
    Figura * figura;
} Interseca;

typedef struct Vector{
    Vertice * a;
    Vertice * b;
} Vector;

struct Color{
    double r;
    double g;
    double b;
};

/**********************************/

extern Foco * lista_focos;
extern Figura * lista_figuras;
extern Ojo * ojo;
extern Frame * frame;
extern Ambiente * ambiente;

/**********************************/


Color * init_color_struct(double r,double g,double b);
Vertice * init_vertice_struct(long double x,long double y,long double z);
Foco * init_foco_struct(long double intensidad, Vertice * vertice);
void init_ojo_struct(Vertice * vertice);
void init_frame_struct(Vertice * bottom_left,Vertice * top_right);
Cara * init_cara_struct();

//Esfera * init_esfera_struct(Color * color, long double radio, Vertice * vertice);
Esfera * init_esfera_struct (Color * color, long double radio, Vertice * vertice, Vertice * kd, long double ka);

Poligono * init_poligono_struct(Color * color);
void init_ambiente_struct(long double iluminacion);


void ins_vertice_cara(Cara * cara, Vertice * vertice);
void ins_cara_poligono(Poligono * poligono, Cara * cara);

//void agregar_figura( void * figura, int tipo_figura, long double * iluminacion);
void agregar_figura(void * figura, int tipo_figura);

void agregar_foco(Foco * foco);


void liberar_esfera(Esfera *esfera);
void liberar_cara(Cara *cara);
void liberar_poligono(Poligono *poligono);
void liberar_figura(int posicion);
void liberar_figuras();
void liberar_ojo();
void liberar_frame();
#endif