#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define PNG_DEBUG 3
#include <png.h>

#include "debug.h"


// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------

#define IMAGE_RED_SHIFT_BITS         0
#define IMAGE_GREEN_SHIFT_BITS       8
#define IMAGE_BLUE_SHIFT_BITS        16
#define IMAGE_ALPHA_SHIFT_BITS       24

#define IMAGE_RGBA(_r, _g, _b, _a) ( (_r << IMAGE_RED_SHIFT_BITS) | (_g << IMAGE_GREEN_SHIFT_BITS) | (_b << IMAGE_BLUE_SHIFT_BITS) | (_a << IMAGE_ALPHA_SHIFT_BITS) )


// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------

int x, y ;

int width, height ;
png_byte color_type, bit_depth ;
png_structp png_ptr ;
png_infop info_ptr ;
int number_of_passes ;


// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------




// ------------------------------------------------------------------------------------------------
// Lee un fichero .png situado en la ruta especificada en el primer parámetro, y guarda información 
// variada en las variables pasadas como punteros.
//
// bpp: Bits por píxel
//
// tamx: Tamaño X en píxels
// tamy: Tamaño Y en píxels
//
// pitchx_bytes: Tamaño en bytes que tiene una línea de la imagen en memoria
//
// pitchx_pixels: Tamaño real en píxels que tiene una línea de la imagen, necesario en máquinas o
//                tarjetas gráficas que no soportan determinados tamaños
//
// pitchy_pixels: Tamaño real en píxels que tiene una columna de la imagen, necesario en máquinas o
//                tarjetas gráficas que no soportan determinados tamaños
//
void *read_png_file(char *file_name, int *bpp, int *tamx, int *tamy, int *pitchx_bytes, int *pitchx_pixels, int *pitchy_pixels)
{
  png_bytep *row_pointers ;
  unsigned char *buffer_temporal ;
  char header[8] ;    // 8 is the maximum size that can be checked
  FILE *fp ;
  int tamx_real_pixels, tamy_real_pixels, tamx_real_bytes ;
  unsigned long *puntero ;
  int varx, vary ;

  ASSERT(file_name) ; ASSERT(bpp) ; ASSERT(tamx) ; ASSERT(tamy) ; ASSERT(pitchx_bytes) ; ASSERT(pitchx_pixels) ; ASSERT(pitchy_pixels) ;

  /* open file and test for it being a png */

  fp = fopen(file_name, "rb") ;
  
  if (!fp) {
    
    printf("\nError: no puedo abrir el fichero %s", file_name) ;
    return(NULL) ;
  }

  fread(header, 1, 8, fp);

  if (png_sig_cmp((png_const_bytep)header, 0, 8)) {
    
    // abort_("[read_png_file] File %s is not recognized as a PNG file", file_name);
    fclose(fp) ;
    return(NULL) ;
  }


  /* initialize stuff */
  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png_ptr) {
    
    //abort_("[read_png_file] png_create_read_struct failed");
    fclose(fp) ;
    return(NULL) ;
  }

  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr) {
    
    //abort_("[read_png_file] png_create_info_struct failed");
    fclose(fp) ;
    return(NULL) ;
  }


//  if (setjmp(png_jmpbuf(png_ptr))) {
//    
//    //abort_("[read_png_file] Error during init_io");
//    fclose(fp) ;
//    return(NULL) ;
//  }


  png_init_io(png_ptr, fp);
  png_set_sig_bytes(png_ptr, 8);

  png_read_info(png_ptr, info_ptr);

  width = png_get_image_width(png_ptr, info_ptr);
  height = png_get_image_height(png_ptr, info_ptr);
  color_type = png_get_color_type(png_ptr, info_ptr);

  bit_depth = png_get_bit_depth(png_ptr, info_ptr);
  if (bit_depth == 16) png_set_strip_16(png_ptr) ;
  

  number_of_passes = png_set_interlace_handling(png_ptr);
  png_read_update_info(png_ptr, info_ptr);

  tamx_real_pixels = width ;
  tamy_real_pixels = height ;
  tamx_real_bytes = width * sizeof(unsigned long) ;

  puntero = (unsigned long *)malloc(tamy_real_pixels * tamx_real_bytes) ;

  if(color_type & PNG_COLOR_MASK_PALETTE) {

    // Ahora podemos leer la paleta y lo copiamos al buffer en 32 bpp

    png_colorp palette ;
    int num_palette ;

    if(png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette) != PNG_INFO_PLTE) {
    
      // Algo raro ha pasado
      //bool bProblema = true ;


    }

    // Si el PNG a leer es de 8 bpp lo que hacemos es leerlo en un buffer temporal y luego lo convertimos a 32

    buffer_temporal = (unsigned char *) malloc(height*png_get_rowbytes(png_ptr, info_ptr)) ;

    row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height) ;
    
    for (vary=0; vary<height; vary++) {
      
      row_pointers[vary] = (png_byte*) buffer_temporal + (vary * png_get_rowbytes(png_ptr, info_ptr)) ;
    }


    png_read_image(png_ptr, row_pointers) ;

    for(vary=0; vary<height; vary++) {

      unsigned char *puntero_lectura = (unsigned char *) row_pointers[vary] ;//buffer_temporal + (vary * png_get_rowbytes(png_ptr, info_ptr)) ;
      unsigned long *puntero_escritura = puntero + (vary*tamx_real_pixels) ; // Falla con CodeWarrior

      for (varx=0; varx<width; varx++) {
      
        int indice = *puntero_lectura ;

        *puntero_escritura = IMAGE_RGBA(palette[indice].red, palette[indice].green, palette[indice].blue, 255) ; // el alpha a 1.0

        puntero_lectura++ ;
        puntero_escritura++ ;
      }
    }    
    
    free(buffer_temporal) ;
    free(row_pointers) ;
  }
  else {

    if(color_type == PNG_COLOR_TYPE_RGB_ALPHA) {

      // Si el PNG a leer es de 32 bpp lo que hacemos es leerlo en un buffer temporal y luego lo convertimos de 32 a 32

      unsigned char *buffer_temporal = (unsigned char *) malloc(height*((sizeof(unsigned char)*4)*width)) ;

      png_bytep *row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height) ;
      
      for (vary=0; vary<height; vary++) {
        
        row_pointers[vary] = (png_byte*) buffer_temporal + (vary * png_get_rowbytes(png_ptr, info_ptr)) ;
      }

      png_read_image(png_ptr, row_pointers) ;



      for(vary=0; vary<height; vary++) {

        unsigned char *puntero_lectura = (unsigned char *) row_pointers[vary] ;//buffer_temporal + (vary * png_get_rowbytes(png_ptr, info_ptr)) ;
        unsigned long *puntero_escritura = puntero + (vary*tamx_real_pixels) ; // Falla con CodeWarrior

        for (varx=0; varx<width; varx++) {

          int r, g, b, a ;

          r = *puntero_lectura ;
          puntero_lectura++ ;

          g = *puntero_lectura ;
          puntero_lectura++ ;

          b = *puntero_lectura ;
          puntero_lectura++ ;

          a = *puntero_lectura ;
          puntero_lectura++ ;

          *puntero_escritura = IMAGE_RGBA(r, g, b, a) ;
          puntero_escritura++ ;
        }
      }    
      
      free(buffer_temporal) ;
      free(row_pointers) ;

    }
    else {

      // Si el PNG a leer es de 24 bpp lo que hacemos es leerlo en un buffer temporal y luego lo convertimos de 24 a 32

      unsigned char *buffer_temporal = (unsigned char *) malloc(height * ((sizeof(unsigned char)*3) * width)) ;
      row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height) ;
      
      for (vary = 0; vary < height; vary++) {
        
        row_pointers[vary] = (png_byte *) buffer_temporal + (vary * png_get_rowbytes(png_ptr, info_ptr)) ;
      }

      png_read_image(png_ptr, row_pointers) ;



      for(vary=0; vary<height; vary++) {

        unsigned char *puntero_lectura = (unsigned char *) row_pointers[vary] ;//buffer_temporal + (vary * png_get_rowbytes(png_ptr, info_ptr)) ;
        unsigned long *puntero_escritura = puntero + (vary*tamx_real_pixels) ; // Falla con CodeWarrior

        int r, g, b ;

        for (varx=0; varx<width; varx++) {
        
          r = *puntero_lectura ;
          puntero_lectura++ ;

          g = *puntero_lectura ;
          puntero_lectura++ ;

          b = *puntero_lectura ;
          puntero_lectura++ ;

          *puntero_escritura = IMAGE_RGBA(r, g, b, 255) ;

          //if(width != *tamx_real_pixels) *puntero_escritura = IMAGE_RGBA(255, 0, 0, 255) ;

          puntero_escritura++ ;
        }
      }    
      
      free(buffer_temporal) ;
      free(row_pointers) ;
    }
  }


  fclose(fp) ;

  *tamx = width ;
  *tamy = height ;

  *bpp = 32 ;

  *pitchx_pixels = tamx_real_pixels ;
  *pitchy_pixels = tamy_real_pixels ;
  *pitchx_bytes = tamx_real_bytes ;

  return puntero ;
}
