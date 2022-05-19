#include "include/main.h"
#include "include/ray_tracer.h"
#include "include/escritura.h"

Color **buffer;
Color * background_color;
int RESOLUCION_H,RESOLUCION_W;

void draw_scene();
void init_buffer();
void init_background(double r, double g, double b);

int main(int argc, char **argv)
{

  RESOLUCION_W = 1008;
  RESOLUCION_H = 567;

  const char *filename = "archivos/figuras.txt";
  if (argc == 3)
  {
    RESOLUCION_W = atoi(argv[1]);
    RESOLUCION_H = atoi(argv[2]);
  }

  init_buffer();
  init_background(0.1,0.1,0.1);
  cargar_figura(filename);
  ray_tracer();
  guardar_imagen();

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(RESOLUCION_W, RESOLUCION_H);
  glutCreateWindow("Proyecto 2 - Ray tracing");
  glClear(GL_COLOR_BUFFER_BIT);
  gluOrtho2D(0, RESOLUCION_W, 0, RESOLUCION_H);
  glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
  glutDisplayFunc(draw_scene);
  glutKeyboardFunc(normal_keys);
  glutKeyboardUpFunc(normal_keys_up);
  glutSpecialFunc(special_keys);
  glutSpecialUpFunc(special_keys_up);
  glutMainLoop();
}

void draw_scene()
{
  int i, j;
  
  glBegin(GL_POINTS);
  for (i = 0; i < RESOLUCION_W; i++)
  {
    for (j = 0; j < RESOLUCION_H; j++)
    {
      glColor3f(buffer[i][j].r, buffer[i][j].g, buffer[i][j].b);
      glVertex2i(i, j);
    }
  }
  glEnd();
  glFlush();
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