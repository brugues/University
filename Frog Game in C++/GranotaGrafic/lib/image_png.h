#ifndef __IMAGE_PNG_INCLUDED_
#define __IMAGE_PNG_INCLUDED_

// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------

//! Lee un fichero .png situado en la ruta especificada en el primer parámetro, y guarda información variada en las variables
//! pasadas como punteros.
//!
//! bpp: Bits por píxel
//!
//! tamx: Tamaño X en píxels
//! tamy: Tamaño Y en píxels
//!
//! pitchx_bytes: Tamaño en bytes que tiene una línea de la imagen en memoria
//!
//! pitchx_pixels: Tamaño real en píxels que tiene una línea de la imagen, necesario en máquinas o tarjetas gráficas que no 
//!                soportan determinados tamaños
//!
//! pitchy_pixels: Tamaño real en píxels que tiene una columna de la imagen, necesario en máquinas o tarjetas gráficas que no 
//!                soportan determinados tamaños
//!
void *read_png_file(char *file_name, int *bpp, int *tamx, int *tamy, int *pitchx_bytes, int *pitchx_pixels, int *pitchy_pixels) ;

#endif
