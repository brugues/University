#include <SDL.h>

#include "libreria.h"
#include "video.h"


struct T_DATOS_VIDEO g_Video ;


// ------------------------------------------------------------------------------------------------
// Pide al sistema operativo que actualice el contenido visible de la ventana
//
void Video_Flip()
{
  SDL_RenderPresent(g_Video.renderer) ;
}




// ------------------------------------------------------------------------------------------------
// Borra el buffer de vídeo
//
void Video_ClearBackBuffer(int r, int g, int b)
{
 SDL_SetRenderDrawColor(g_Video.renderer, (Uint8)r, (Uint8)g, (Uint8)b, 255) ;
 SDL_RenderClear(g_Video.renderer) ;
}




// ------------------------------------------------------------------------------------------------
// Muestra la ventana
//
void Video_ShowWindow()
{
  SDL_ShowWindow(g_Video.window) ;
}




// ------------------------------------------------------------------------------------------------
// Inicializa la ventana con el tamaño especificado
//
int Video_Init(int new_resx, int new_resy, int bFullScreen)
{
  Uint32 flags = /*SDL_WINDOW_OPENGL | */SDL_WINDOW_HIDDEN ;

  //flags |= SDL_WINDOW_RESIZABLE /*| SDL_WINDOW_MAXIMIZED*/ ;

  if(bFullScreen) {
  
    flags |= SDL_WINDOW_FULLSCREEN ;
  }

#ifdef __APPLE__
  
  // On iOS your application will have a status bar on top that shows the carrier and battery levels. 
  // For games you often want the extra 12 pixel from the top and have this bar hidden. All you need 
  // to do to hide the status bar is passing SDL_WINDOW_BORDERLESS as additional flag to the 
  // SDL_CreateWindow function call

  flags |= SDL_WINDOW_BORDERLESS ;

  // If you want to respond to rotation events of the phone you will need to pass the SDL_WINDOW_RESIZABLE 
  // flag to SDL_CreateWindow. Whenever the device is rotated, SDL will switch width and height and fire an 
  // SDL_WINDOWEVENT with the window.event flag set to SDL_WINDOWEVENT_RESIZED

  //flags |= SDL_WINDOW_RESIZABLE ;

#endif

  g_Video.resx = new_resx ;
  g_Video.resy = new_resy ;

  // Create the window where we will draw.

  g_Video.window   = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, new_resx, new_resy, flags) ;
  g_Video.renderer = SDL_CreateRenderer(g_Video.window, -1, (SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) ;

  if (!g_Video.renderer) {

    return FALSE ;
  }


  //{
  //  SDL_Rect rect ;
  //
  //  rect.h = new_resx ;
  //  rect.w = new_resy ;
  //
  //  rect.x = 0 ;
  //  rect.y = 0 ;
  //
  //  SDL_RenderSetViewport(g_Video.renderer, &rect) ;
  //}

  return TRUE ;
}




// ------------------------------------------------------------------------------------------------
//
//
void Video_Release()
{
  SDL_DestroyRenderer(g_Video.renderer) ;
  SDL_DestroyWindow(g_Video.window) ;
}

