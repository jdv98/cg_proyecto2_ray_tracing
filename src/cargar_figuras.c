#include "include/read_file.h"
#include "include/tipo_poligono.h"
#include "include/cargar_figuras.h"
#include <malloc.h>

static void error(int num){
    (void)fprintf(stdout, "CARGAR_FIGURA #%i\n",num);
    exit(0);
}

double leer_numero()
{
    bool init = true;
    double num = 0;

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
            num += (double)(get_char_iter() - 48) / decimales;
            decimales *= 10;
            inc_iter();
        }
    }
    return num;
}

void leer_poligono()
{
    if (inc_iter_if_cmp('{'))
    {

    }
    if (!inc_iter_if_cmp('}'))
        error(3);
}

void leer_esfera()
{
    if (inc_iter_if_cmp('{'))
    {
        
    }
    if (!inc_iter_if_cmp('}'))
        error(2);
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
        error(1);
}

void cargar_figura(const char *filename)
{
    int size = 0;
    char *original = read_file(filename, &size);
    asignar_iter(original, size);

    // INIT

    // LECTURA
    while (seguir_iter())
    {
        leer_figura();
    }

    free(original);
    if(size==0)
        error(0);
}