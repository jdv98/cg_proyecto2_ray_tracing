#include "include/escritura.h"
#include "include/dibujar.h"

void guardar_imagen(){
    char * nombre="imagen.jpg";
    size_t number_wands = 0;
    PixelIterator * pixel_iterator;

    // Inicializaciones
    MagickWandGenesis();
    MagickWand *magick_wand = NewMagickWand();
    PixelWand * background_pixel_image = NewPixelWand();

    {
        // definicion del fondo
        PixelSetColor(background_pixel_image, "black");

        //Crea imagen de fondo negro
        MagickBooleanType status = MagickNewImage(magick_wand, RESOLUCION_W, RESOLUCION_H, background_pixel_image);
        if (status == MagickFalse)
            ThrowWandException(magick_wand);
        MagickResetIterator(magick_wand);
        MagickNextImage(magick_wand);

        pixel_iterator = NewPixelIterator(magick_wand);
        escribir_imagen(magick_wand, pixel_iterator, number_wands);
        DestroyPixelIterator(pixel_iterator);

        status = MagickWriteImage(magick_wand, nombre);
        if (status == MagickFalse)
            ThrowWandException(magick_wand);
    }

    magick_wand = DestroyMagickWand(magick_wand);
    MagickWandTerminus();
}

void escribir_imagen(MagickWand *magick_wand, PixelIterator * pixel_iterator, size_t number_wands){
    PixelResetIterator(pixel_iterator);
    PixelWand ** pixel_wand_row = PixelGetCurrentIteratorRow(pixel_iterator, &number_wands);
    int row = MagickGetImageHeight(magick_wand)-1;
    do
    {

        for (size_t i = 0; i < number_wands; i++)
        {
            PixelSetRed(pixel_wand_row[i], buffer[i][row].r);
            PixelSetGreen(pixel_wand_row[i], buffer[i][row].g);
            PixelSetBlue(pixel_wand_row[i], buffer[i][row].b);
            PixelSyncIterator(pixel_iterator);
        }
        pixel_wand_row = PixelGetNextIteratorRow(pixel_iterator, &number_wands);
        row--;
    } while (number_wands > 0);
}