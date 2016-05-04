#ifndef __SOUND_INCLUDED_
#define __SOUND_INCLUDED_

#include "stb_vorbis.h"

// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------


//! Número máximo de sonidos sonando de manera simultánea

#define MAX_SIMULTANEOUS_SOUND_CHANNELS                                  8

//! El número máximo de canales reservados a efectos de sonido es el total menos el de la música y el del ambiente

#define MAX_SIMULTANEOUS_SOUND_CHANNELS_FOR_SOUND_EFFECTS                (MAX_SIMULTANEOUS_SOUND_CHANNELS - 1 - 1)


//! Tipos de streaming

enum {

  //! Reproducir desde un buffer de memoria (Ideal para sonidos pequeños)
  PLAY_FROM_MEMORY,

  //! Reproducir cargando poco a poco desde disco (Ideal / Necesario para sonidos grandes)
  PLAY_FROM_DISK_STREAM
} ;


//! Tipos de loop

enum {

  //! Cuando le damos al play el sonido suena desde el principio si estaba parado, o continúa por donde iba si estaba en pause
  SOUND_PLAY_NORMAL,

  //! Si el sonido ya estaba reproduciéndose lo deja continuar en vez de hacer que vuelva al principio
  SOUND_DO_NOT_RESTART_IF_ALREADY_PLAYING,

  //! El sonido vuelve a comenzar desde el principio INCLUSO si sólo estaba pausado
  SOUND_FORCE_RESTART,
} ;




//! Tipos de loop

enum {

  //! El sonido se detiene al llegar al final
  PLAY_THEN_STOP_AT_END,

  //! El sonido vuelve a comenzar cuando acaba
  PLAY_THEN_LOOP_AT_END
} ;


//! Estados en los que puede estar un sonido

enum {

  //! El sonido está parado, y cuando comience a reproducirse de nuevo lo hará desde el principio
  SOUND_STATE_STOPPED,

  //! El sonido está pausado, y cuando comience a reproducirse de nuevo lo hará desde donde se quedó al pausarlo
  SOUND_STATE_PAUSED,

  //! El sonido está reproduciéndose
  SOUND_STATE_PLAYING
} ;


// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------

struct T_SOUND
{
  //! Longitud en samples del sonido
  int num_samples ;

  //! Posición en la que se encuentra del stream
  int posicion_stream ;
	
  //! Indica el modo de loop del sonido
  int bLoop ;

  //! Indica en qué estado se encuentra el sonido
  int estado ;

  //! Puntero al buffer de almacenamiento si se reproduce desde memoria, NULL si se reproduce desde disco
  unsigned char *buffer_fichero ;

  //! Posición que está ocupando en la cola, en caso de estar playeándose
  int posicion_cola ;

  //! Puntero a una estructura de datos de la librería stb_vorbis
  stb_vorbis *ogg ;
} ;


// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------

//! Inicializa la librería de sonido
void Sound_Init() ;

//! Libera los recursos alojados por la librería de sonido
void Sound_Release() ;

//struct T_SOUND *Sound_LoadFileStream(char *path, int bLoop) ;
//struct T_SOUND *Sound_LoadMemoryStream(char *path, int bLoop) ;

//! Función de alto nivel que automatiza la carga y reproducción de la música de fondo
struct T_SOUND *Sound_LoadMusic(char *path, int bStream) ;

//! Carga un sonido y lo deja listo para comenzar a usarlo
struct T_SOUND *Sound_LoadSound(char *path) ;

//! Comienza la reproducción del sonido pasado como parámetro. Devuelve el número de slot que empleará el sonido para reproducirse, o NO_SOUND_CHANNEL_AVAILABLE si no queda ninguno libre
int Sound_Play(struct T_SOUND *sonido, int mode) ;

//! Pausa la reproducción del sonido pasado como parámetro
void Sound_Pause(struct T_SOUND *sonido) ;

//! Detiene la reproducción del sonido pasado como parámetro
void Sound_Stop(struct T_SOUND *sonido) ;

//! Reinicia la reproducción del sonido pasado como parámetro
void Sound_Restart(struct T_SOUND *sonido) ;

//! Borra el sonido pasado como parámetro y libera los recursos que haya podido alojar
void Sound_Delete(struct T_SOUND *sonido) ;

#endif