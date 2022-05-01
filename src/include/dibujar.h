#ifndef DIBUJAR_H
#define DIBUJAR_H

#include <stddef.h>
#include <stdbool.h>

typedef struct {
  double r;
  double g;
  double b;
} COLOR;

extern COLOR **buffer;

extern int RESOLUCION_H;
extern int RESOLUCION_W;

#endif