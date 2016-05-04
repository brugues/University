#ifndef __SPRITES_INCLUDED_
#define __SPRITES_INCLUDED_

#include <SDL.h>

#pragma warning (disable : 4200)


// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------

enum {

  SPRITES_LOOP_OFF,
  SPRITES_LOOP_ON,
} ;


#define SPRITE_WILL_BE_ANIMATED                           NULL

enum {

    DO_NOT_OVERWRITE_SAME_ANIMATION,
    OVERWRITE_SAME_ANIMATION
} ;

// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------

//! Esta estructura auxiliar sirve para poder hacer listas de frames de animación y sus propiedades

struct T_DESCRIPCION_FRAME_ANIMACION
{
  //! Duración del frame en frames de juego
  int duracion ;

  //! Posición X del hotpoint
  int hx ;

  //! Posición Y del hotpoint
  int hy ;

  //! Ruta del fichero que contiene el frame
  char *ruta ;
} ;


//! Esta estructura auxiliar sirve para poder hacer tablas de animación

struct T_DESCRIPCION_ANIMACION
{
  //! Este campo especifica qué sucede cuando la animación llega al final: se para o comienza de nuevo.
  int modo_loop ;

  //! Número de frames de la animación
  int num_frames ;

  //! Lista terminada de punteros a frame
  struct T_DESCRIPCION_FRAME_ANIMACION *descripcion_frames[] ;
} ;


//! Estructura de datos que contiene la información necesaria para tener en memoria una imagen y 
//! poderla dibujar, y datos extra como la duración y el hotpoint

struct T_FRAME
{
  //! Duración del frame en X unidad
  int duracion ;

  //! Puntero a una textura acelerada por hardware de SDL
  SDL_Texture *texture ;

  //! Puntero a un buffer de píxels de SDL
  SDL_Surface *surface ;

  //! Puntero al buffer de píxels
  unsigned long *pixels ;

  //! Tamaño X en píxels
  int tamx ;

  //! Tamaño Y en píxels
  int tamy ;

  //! Hotpoint X
  int hx ;

  //! Hotpoint Y
  int hy ;
} ;


//! Una animación es una lista de frames

struct T_ANIMATION
{
  //! Número de frames que tiene la animación
  int num_frames ;

  //! Este campo especifica qué sucede cuando la animación llega al final: se para o comienza de nuevo.
  int tiene_loop ;

  //! Puntero a un array de punteros de frame
  struct T_FRAME **frames ;
} ;




//! Un sprite es un objeto de "alto nivel" que nos ayuda a trabajar con frames y animaciones

struct T_SPRITE
{
  //! Posición por la que vamos del frame actual de la animación
  float posicion_animacion ;

  //! Velocidad a la que funciona la animación del sprite
  float velocidad_animacion ;

  //! Puntero al frame actual de la animación
  struct T_FRAME *frame_actual ;

  //! Número de frame en la animación actual
  int num_frame_actual ;
  
  //! Indica si la animación ha llegado a terminarse o no
  int animacion_completada ;

  //! Puntero a la animación actual
  struct T_ANIMATION *animacion ;

  //! Multiplicador de tamaño X
  float scalex ;

  //! Multiplicador de tamaño Y
  float scaley ;
} ;


// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------

// Crea un sprite, vacío si ruta == NULL, o con un frame conteniendo el .png situado en la ruta
struct T_SPRITE *Sprite_Create(char *ruta) ;

//! Borra un sprite y libera todos los recursos que hubiese podido alojar
void Sprite_Delete(struct T_SPRITE *sprite) ;

//! Dibuja un sprite en las coordenadas especificadas
void Sprite_Draw(struct T_SPRITE *sprite, int x, int y) ;

//! Cambia la animación del sprite
void Sprite_SetAnimation(struct T_SPRITE *sprite, struct T_ANIMATION *anim, int bOverWrite) ;

//! Cambia el frame de la animación del sprite
void Sprite_SetFrame(struct T_SPRITE *sprite, int num_frame) ;

//! Realiza el proceso necesario en el sprite (por ejemplo la animación)
void Sprite_Tick(struct T_SPRITE *sprite) ;

//! Velocidad a la que se animará el sprite
void Sprite_SetAnimationSpeed(struct T_SPRITE *sprite, float speed) ;

//! Crea un frame y devuelve el puntero a él
struct T_FRAME *Sprites_CreateFrame(char *ruta) ;

//! Libera los recursos que tenga alojados un frame
void Sprites_ReleaseFrame(struct T_FRAME *frame) ;

//! Crea una nueva animación con los .png ordenados de un directorio
struct T_ANIMATION *Sprites_CreateAnimation(struct T_DESCRIPCION_ANIMACION *descripcion_anim) ;

//! Libera los recursos que tenga alojados una animación
void Sprites_ReleaseAnimation(struct T_ANIMATION *anim) ;

//! Escala el tamaño del sprite por el factor indicado
void Sprite_SetScale(struct T_SPRITE *sprite, float scale) ;

//! Escala el tamaño horizontal del sprite por el factor indicado
void Sprite_SetScaleX(struct T_SPRITE *sprite, float scalex) ;

//! Escala el tamaño vertical del sprite por el factor indicado
void Sprite_SetScaleY(struct T_SPRITE *sprite, float scaley) ;


#endif
