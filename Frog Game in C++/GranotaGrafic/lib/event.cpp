#include "event.h"

#ifdef _WIN32

  #include <windows.h>

  #include <crtdbg.h>
  #include <time.h>

  // Esto puede parecer extraño, pero es necesario si el proyecto 
  // es de "línea de comandos" en Visual Studio y vamos a usar SDL  

  #undef main

#endif

#include <SDL.h>
#include "libreria.h"



// ------------------------------------------------------------------------------------------------
//
//
void Procesar_Bucle_De_Mensajes_SDL(t_programStatus &g_ProgramStatus)
{
  SDL_Event event;

  // Mientras haya eventos en la cola nos quedamos en el bucle y los procesamos

  while (SDL_PollEvent(&event)) {

    switch (event.type)
    {
      // Application events ------------------------------------------------------------------------
        
      case SDL_QUIT: // User-requested quit
        
        g_ProgramStatus.bExit = TRUE ;
        
        break ;
        
      // Window events -----------------------------------------------------------------------------
        
      case SDL_WINDOWEVENT:            // Window state change

        // --------------------------------------------------------------------------
        // --------------------------------------------------------------------------
        
        switch (event.window.event) {
            
          case SDL_WINDOWEVENT_MINIMIZED:
            g_ProgramStatus.bMinimized = TRUE ;
            break;
            
          case SDL_WINDOWEVENT_RESTORED:
            g_ProgramStatus.bMinimized = FALSE ;
            break;
            
          default:

            break;
        } ;

        // --------------------------------------------------------------------------
        // --------------------------------------------------------------------------
            
        break ;
        
      // Keyboard events ---------------------------------------------------------------------------
        
      case SDL_KEYDOWN:  // Key pressed

        // Quitar comentario si sólo queremos hacemos caso de pulsaciones "reales" y no producto de los settings de repetición

//        if(!event.key.repeat) {
          
          Keyboard_ProcessKeyDown(event.key.keysym.sym) ;
//        }
        
        break ;
        
      case SDL_KEYUP: // Key released

        Keyboard_ProcessKeyUp(SDL_GetScancodeFromKey(event.key.keysym.sym)) ;

        break ;
        
      // Mouse events ------------------------------------------------------------------------------
        
      case SDL_MOUSEBUTTONDOWN:        /**< Mouse button pressed */
        
        Mouse_ProcessButtonDown(event.button.button) ;
        
        break ;
        
      case SDL_MOUSEBUTTONUP:          /**< Mouse button released */
        
        Mouse_ProcessButtonUp(event.button.button) ;
        
        break ;
        
      case SDL_MOUSEWHEEL:             /**< Mouse wheel motion */
      
        Mouse_ProcessWheel(event.wheel.x, event.wheel.y) ;
        
        break ;
        
      default:

        break ;
    } ;
  }

}




// ------------------------------------------------------------------------------------------------
//
//
void InitEventSystem()
{

}




// ------------------------------------------------------------------------------------------------
//
//
void ProcessEventSystem(t_programStatus &g_ProgramStatus)
{
  Procesar_Bucle_De_Mensajes_SDL(g_ProgramStatus) ;
}




// ------------------------------------------------------------------------------------------------
//
//
void SendExitEvent(t_programStatus &g_ProgramStatus)
{
  g_ProgramStatus.bExit = TRUE ;
}




// ------------------------------------------------------------------------------------------------
//
//
int InitializeHardware(int new_resolution_x, int new_resolution_y, int fps_maximos, int bFullScreen)
{
  if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {

    printf("\nUnable to init SDL: %s", SDL_GetError() ) ;
    return(FALSE) ;
  }


#ifdef ACTIVAR_CONSOLA_DE_DEBUG

  #ifndef __APPLE__

    // SDL_Init() routes stdout and stderr to the respective files. 
    // You can revert this by adding the following lines AFTER the 
    // call to SDL_Init in your code:  

    freopen( "CON", "w", stdout ) ;
    freopen( "CON", "w", stderr ) ;

  #endif

#endif

  Keyboard_Init() ;
  Mouse_Init() ;

  Video_Init(new_resolution_x, new_resolution_y, bFullScreen) ;

  // make sure SDL cleans up before exit
  atexit(SDL_Quit) ;

  return(TRUE) ;
}




// ------------------------------------------------------------------------------------------------
//
//
void SincronizarProximoFrame()
{


}


int InitGame (t_programStatus &g_ProgramStatus)
{
	// Pedimos que se inicialice la ventana del juego y establecemos como límite máximo 60 fps
    if(!InitializeHardware(RESOLUTION_X, RESOLUTION_Y, MAX_FPS, RUN_IN_WINDOW_MODE)) 
		return PROGRAM_EXIT_ERROR;

	// Cosas de Windows - Pedimos funcionar en alta prioridad, mejora la estabilidad del dibujado y el sonido
#ifdef _WIN32
  SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS) ;
#endif

	// Inicializamos las variables de estado del programa
    memset(&g_ProgramStatus, 0, sizeof(struct T_PROGRAM_STATUS)) ;


	// Inicializamos el sistema de lectura de eventos de Windows
	InitEventSystem() ;
}


void ProcessEvents (t_programStatus &g_ProgramStatus)
{
	// Borramos el buffer de vídeo antes de hacer la espera porque así aprovechamos mejor
	// el tiempo en vez de esperar para luego ponernos a borrar cuando nos toca procesar
	Video_ClearBackBuffer(255, 255, 0) ;

	// Esperamos a que llegue el momento de empezar a dibujar
	SincronizarProximoFrame() ;

	// Procesamos el teclado
	Keyboard_Tick() ;

	// Procesamos el ratón
	Mouse_Tick() ;

	// Procesamos los eventos que pueda habernos metido en la cola el sistema operativo
	ProcessEventSystem(g_ProgramStatus) ;
}


void VideoUpdate(t_programStatus &g_ProgramStatus)
{
	// Incrementamos el número de frame actual
	g_ProgramStatus.CurrentFrameNumber++ ;

	// Pedimos al sistema operativo que actualice el contenido de la ventana
	Video_Flip() ;

}



