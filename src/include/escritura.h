#ifndef ESCRITURA_H
#define ESCRITURA_H

#include <MagickWand/MagickWand.h>


#define ThrowWandException(wand) \
{ \
  char \
    *description; \
 \
  ExceptionType \
    severity; \
 \
  description=MagickGetException(wand,&severity); \
  (void) fprintf(stderr,"%s %s %lu %s\n",GetMagickModule(),description); \
  description=(char *) MagickRelinquishMemory(description); \
  exit(-1); \
}

void guardar_imagen();
void escribir_imagen(MagickWand *magick_wand, PixelIterator * pixel_iterator, size_t number_wands);



#endif