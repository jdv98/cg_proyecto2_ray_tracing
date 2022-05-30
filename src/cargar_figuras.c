#include "include/read_file.h"
#include "include/tipo_figura.h"
#include "include/cargar_figuras.h"
#include "include/estructuras.h"
#include <malloc.h>
#include <string.h>

long double leer_numero();

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
    }

    *pw = '\0';
    (*size)=strlen(str);
}

long double * leer_iluminacion_figura(){
    long double * datos = malloc(sizeof(long double) * 4);

    if(!inc_iter_if_cmp('{'))
        error("{-> iluminacion figura");
    
    long double kd=leer_numero();
    if(kd>1)
        kd=1;
    else if(kd<0)
        kd=0;

    if(!inc_iter_if_cmp(','))
        error(",-> iluminacion figura");

    long double ka=leer_numero();
    if(ka>1)
        ka=1;
    else if(ka<0)
        ka=0;

    if(!inc_iter_if_cmp(','))
        error(",-> iluminacion figura");
    
    long double kn=leer_numero();


    if(!inc_iter_if_cmp(','))
        error(",-> iluminacion figura");

    long double ks=leer_numero();


    if(!inc_iter_if_cmp('}'))
        error("}-> iluminacion figura");
    
    datos[0]=kd;
    datos[1]=ka;
    datos[2]=kn;
    datos[3]=ks;

    return datos;
}

long double leer_numero()
{
    bool init = true;
    long double num = 0;
    bool negativo=inc_iter_if_cmp('-');

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
    return negativo?(-1*num):num;
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

void leer_poligono(Color * color, long double * iluminacion){
    Poligono * poligono = init_poligono_struct(color, iluminacion);

    if (inc_iter_if_cmp('{'))
    {
        while (inc_iter_if_cmp('[')){
            
            while (!inc_iter_if_cmp(']'))
            {
                ins_vertice_poligono(poligono,leer_vertice());
                if(inc_iter_if_cmp(','));
            }
            agregar_figura(poligono,POLIGONO);

            if(inc_iter_if_cmp(',')){
                poligono = init_poligono_struct(color, iluminacion);
            }
        }
    }
    if (!inc_iter_if_cmp('}'))
        error("poligono");
    
    free(iluminacion);
}

void leer_ojo(){
    init_ojo_struct(leer_vertice());
}

void leer_frame(){
    Vertice * bl, * tr;
    bl=leer_vertice();
    inc_iter_if_cmp(',');
    tr=leer_vertice();
    
    init_frame_struct(bl,tr);
}

void leer_figura()
{
    Color * color = leer_color();
    inc_iter_if_cmp(',');
    long double * iluminacion=leer_iluminacion_figura();
    inc_iter_if_cmp(',');

    leer_poligono(color, iluminacion);
}

void leer_esfera()
{
    Color * color = leer_color();
    inc_iter_if_cmp(',');
    long double * iluminacion=leer_iluminacion_figura();    
    inc_iter_if_cmp(',');
    Vertice * vertice = leer_vertice();
    inc_iter_if_cmp(',');
    long double radio=leer_numero();

    agregar_figura(init_esfera_struct(color,radio,vertice,iluminacion),ESFERA);
}

void leer_foco(){
    long double * datos = malloc(sizeof(long double)*4);

    if (inc_iter_if_cmp('{'))
    {
        datos[0] = leer_numero();
        if(!inc_iter_if_cmp(','))
            error("foco");

        datos[1] = leer_numero();
        if(!inc_iter_if_cmp(','))
            error("foco");
        
        datos[2] = leer_numero();
        if(!inc_iter_if_cmp(','))
            error("foco");
        
        datos[3] = leer_numero();
    }
    if (!inc_iter_if_cmp('}'))
        error("foco");
    
    if(!inc_iter_if_cmp(','))
        error("foco");

    Vertice * vertice = leer_vertice();
    agregar_foco(init_foco_struct(datos,vertice));
}

void leer_ambiente(){
    if(get_char_iter() > 47 && get_char_iter() < 58){
        init_ambiente_struct(leer_numero());
    }
    else{
        error("ambiente");
    }
}

void leer_escenario()
{
    if (inc_iter_if_cmp('{'))
    {
        int tipo_figura = (int)leer_numero();
        if(!inc_iter_if_cmp(','))
            error(", despues de id");

        if(tipo_figura == FOCO)
            leer_foco();

        else if (tipo_figura == ESFERA)
            leer_esfera();

        else if(tipo_figura == POLIGONO)
            leer_figura();
        
        else if(tipo_figura == OJO)
            leer_ojo();

        else if(tipo_figura == FRAME)
            leer_frame();
        
        else if(tipo_figura == AMBIENTE)
            leer_ambiente();
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
        leer_escenario();
    }

    free(original);
    if(size==0)
        error("carga");
}