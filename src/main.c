#include "include/main.h"
#include "include/ray_tracer.h"
#include "include/escritura.h"
#include <string.h>

Color **buffer;
Color * background_color;
int RESOLUCION_H,RESOLUCION_W;

void init_buffer();
void init_background(double r, double g, double b);

int main(int argc, char **argv)
{

  RESOLUCION_W = 1008;
  RESOLUCION_H = 567;
  char * nombre_escenario="escenario";
  char * tipo_imagen = "avs";

  if(argc == 2){
    nombre_escenario=argv[1];
  }
  else if (argc == 3)
  {
    nombre_escenario=argv[1];
    tipo_imagen =argv[2];
  }
  else if (argc == 5)
  {
    nombre_escenario=argv[1];
    tipo_imagen=argv[2];
    RESOLUCION_W = atoi(argv[3]);
    RESOLUCION_H = atoi(argv[4]);
  }

  
  char * nombre_imagen = malloc(sizeof(char)*(strlen(nombre_escenario)+strlen(tipo_imagen)));
  sprintf(nombre_imagen, "%s.%s", nombre_escenario,tipo_imagen);

  const char * filename = malloc(sizeof(char)*(strlen(nombre_escenario)+14));
  sprintf(filename, "archivos/%s.txt", nombre_escenario);

  init_buffer();
  init_background(0.1,0.1,0.1);
  cargar_figura(filename);
  ray_tracer();
  guardar_imagen(nombre_imagen);
}

void init_buffer(){
  int i, j;

  buffer = (Color **)malloc(RESOLUCION_W * sizeof(Color));
  for (i = 0; i < RESOLUCION_W; i++)
  {
    buffer[i] = (Color *)malloc(RESOLUCION_H * sizeof(Color));
  }

  for (i = 0; i < RESOLUCION_W; i++)
  {
    for (j = 0; j < RESOLUCION_H; j++)
    {
      buffer[i][j].r = 0.0;
      buffer[i][j].g = 0.0;
      buffer[i][j].b = 0.0;
    }
  }
}

void init_background(double r, double g, double b){
  background_color=malloc(sizeof(Color));
  background_color->r=r;
  background_color->g=g;
  background_color->b=b;
}