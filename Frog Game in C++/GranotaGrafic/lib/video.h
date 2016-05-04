#ifndef __VIDEO_INCLUDED_
#define __VIDEO_INCLUDED_

#include <SDL.h>

// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------


#define VIDEO_MASCARA_R                 0x000000FF
#define VIDEO_MASCARA_G                 0x0000FF00
#define VIDEO_MASCARA_B                 0x00FF0000
#define VIDEO_MASCARA_A                 0xFF000000

#define VIDEO_SHIFT_R                   0
#define VIDEO_SHIFT_G                   8
#define VIDEO_SHIFT_B                   16
#define VIDEO_SHIFT_A                   24

#define RUN_IN_WINDOW_MODE              0
#define RUN_IN_FULLSCREEN_MODE          1



// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------

//! En esta estructura se guarda el status del control de vídeo

struct T_DATOS_VIDEO
{
  int resx ;
  int resy ;

  SDL_Window *window ;
  SDL_Renderer *renderer ;
} ;



// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------

//! Inicializa la ventana con el tamaño especificado
int Video_Init(int new_resx, int new_resy, int bFullScreen) ;

//! Borra el buffer de vídeo
void Video_ClearBackBuffer(int r, int g, int b) ;

//! Muestra la ventana
void Video_ShowWindow() ;

//! Pide al sistema operativo que actualice el contenido visible de la ventana
void Video_Flip() ;

void Video_Release();

// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------

// Extern para acceder a la variable de status de vídeo
extern struct T_DATOS_VIDEO g_Video ;

#endif
