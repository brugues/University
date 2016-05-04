#ifndef __EVENT_INCLUDED
#define __EVENT_INCLUDED

// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------

#define ACTIVAR_CONSOLA_DE_DEBUG

#define RESOLUTION_X                      600
#define RESOLUTION_Y                      550

#define MAX_FPS                           60
#define PROGRAM_EXIT_STATUS_OK            0
#define PROGRAM_EXIT_ERROR                -1


// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------

typedef struct T_PROGRAM_STATUS
{
  int bExit ;
  int bMinimized ;
  int CurrentFrameNumber;
} t_programStatus;


void Procesar_Bucle_De_Mensajes_SDL(t_programStatus &g_ProgramStatus);
void InitEventSystem();
void ProcessEventSystem(t_programStatus &g_ProgramStatus);
void SendExitEvent(t_programStatus &g_ProgramStatus);
int InitializeHardware(int new_resolution_x, int new_resolution_y, int fps_maximos, int bFullScreen);
void SincronizarProximoFrame();
int InitGame (t_programStatus &g_ProgramStatus);
void ProcessEvents (t_programStatus &g_ProgramStatus);
void VideoUpdate(t_programStatus &g_ProgramStatus);


#endif
