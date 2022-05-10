#include "include/read_file.h"
#include "include/tipo_figura.h"
#include "include/cargar_figuras.h"
#include "include/estructuras.h"
#include <malloc.h>

static void error(char * err){
    (void)fprintf(stdout, "CARGAR_FIGURA #%s\n",err);
    exit(0);
}

void remove_all_chars(char* str, int * size, char * c, int size_c) {
    char *pr = str, *pw = str;
    bool conservar=true;

    while(*pw)
    {
        conservar=true;
        *pw = *pr;
        *pr++;

        for (size_t i = 0; i < size_c; i++)
        {
            conservar=((*pw!=c[i]) && conservar);
        } 
        if(conservar)
            pw +=1;
        else
            (*size)--;
    }

    *pw = '\0';
}

long double leer_numero()
{
    bool init = true;
    long double num = 0;

    while (get_char_iter() > 47 && get_char_iter() < 58)
    {
        if (init)
        {
            num += get_char_iter() - 48;
            init = false;
        }
        else
        {
            num *= 10;
            num += get_char_iter() - 48;
        }
        inc_iter();
    }
    if (cmp_iter_char('.'))
    {
        inc_iter();
        int decimales = 10;

        while (get_char_iter() > 47 && get_char_iter() < 58)
        {
            num += (long double)(get_char_iter() - 48) / decimales;
            decimales *= 10;
            inc_iter();
        }
    }
    return num;
}

Color * leer_color(){
    Color * color=NULL;
    if (inc_iter_if_cmp('{'))
    {
        double r=leer_numero();
        if (!inc_iter_if_cmp(',')) error("color");
        double g=leer_numero();
        if (!inc_iter_if_cmp(',')) error("color");
        double b=leer_numero();

        color = init_color_struct(r,g,b);
    }
    if (!inc_iter_if_cmp('}'))
        error("color");

    return color;
}

Vertice * leer_vertice(){

    Vertice * vertice=NULL;

    if (inc_iter_if_cmp('{'))
    {
        long double x=leer_numero();
        if (!inc_iter_if_cmp(',')) error("vertice");
        long double y=leer_numero();
        if (!inc_iter_if_cmp(',')) error("vertice");
        long double z=leer_numero();

        vertice = init_vertice_struct(x,y,z);
    }
    if (!inc_iter_if_cmp('}'))
        error("vertice");
    return vertice;
}

void leer_caras(Poligono * poligono){
    Cara * cara;
    if (inc_iter_if_cmp('{'))
    {
        while (inc_iter_if_cmp('[')){
            cara = init_cara_struct();
            while (!inc_iter_if_cmp(']'))
            {
                ins_vertice_cara(cara,leer_vertice());
                if(inc_iter_if_cmp(','));
            }
            ins_cara_poligono(poligono,cara);
            inc_iter_if_cmp(',');
        }
        
    }
    if (!inc_iter_if_cmp('}'))
        error("cara");
}

void leer_poligono()
{
    Poligono * poligono = init_poligono_struct(leer_color());
    inc_iter_if_cmp(',');
    leer_caras(poligono);
    agregar_figura(poligono,POLIGONO);
}

void leer_esfera()
{
    Color * color = leer_color();
    inc_iter_if_cmp(',');
    Vertice * vertice = leer_vertice();
    inc_iter_if_cmp(',');
    long double radio=leer_numero();

    agregar_figura(init_esfera_struct(color,radio,vertice),ESFERA);
}

void leer_figura()
{
    if (inc_iter_if_cmp('{'))
    {
        int tipo_figura = (int)leer_numero();

        if (tipo_figura == ESFERA)
            leer_esfera();

        else if(tipo_figura == POLIGONO)
            leer_poligono();
    }
    if (!inc_iter_if_cmp('}'))
        error("figura");
}

void cargar_figura(const char *filename)
{
    int size = 0;
    char *original = read_file(filename, &size);
    remove_all_chars(original,&size, (char[]){32,'\n'},2);
    asignar_iter(original, size);

    // INIT

    // LECTURA
    while (seguir_iter())
    {
        leer_figura();
    }

    free(original);
    if(size==0)
        error("carga");
}