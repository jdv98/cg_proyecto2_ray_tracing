#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#define EPSILON 0.00000000005

/**********************************/

typedef struct Vertice Vertice;
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

struct Esfera{
    Color * color;
    long double k_d; //Coeficiente de reflexion difusa
    long double k_a; //Coeficiente de iluminacion ambiente
    Vertice * vertice;
    long double radio;
};

struct Poligono{
    Color * color;
    long double k_d; //Coeficiente de reflexion difusa
    long double k_a; //Coeficiente de iluminacion ambiente
    int cant_vertices;
    Vertice * * vertices;
    long double * ecuacion_plano;
    Vertice * vector_normal;
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

struct Foco
{
    long double intensidad;
    long double c1_f_att;
    long double c2_f_att;
    long double c3_f_att;
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
Foco * init_foco_struct(long double * datos, Vertice * vertice);
void init_ojo_struct(Vertice * vertice);
void init_frame_struct(Vertice * bottom_left,Vertice * top_right);
Esfera * init_esfera_struct (Color * color, long double radio, Vertice * vertice, long double * iluminacion);
Poligono * init_poligono_struct(Color * color, long double * iluminacion);
void init_ambiente_struct(long double iluminacion);

void ins_vertice_poligono(Poligono * poligono, Vertice * vertice);
void agregar_figura(void * figura, int tipo_figura);
void agregar_foco(Foco * foco);


void liberar_interseca(Interseca * interserca);
void liberar_esfera(Esfera *esfera);
void liberar_poligono(Poligono *poligono);
void liberar_figura(int posicion);
void liberar_figuras();
void liberar_ojo();
void liberar_frame();


long double obtener_kd_figura(void * figura, int tipo);
long double obtener_ka_figura(void * figura, int tipo);
Color * obtener_color(void * figura, int tipo);
#endif