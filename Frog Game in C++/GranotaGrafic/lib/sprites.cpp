#include <stdlib.h>
#include <malloc.h>

#include "libreria.h"
#include "sprites.h"



// ------------------------------------------------------------------------------------------------
// Crea un sprite, vacío si ruta == SPRITE_WILL_BE_ANIMATED, o con un frame conteniendo el .png 
// situado en la ruta
//
struct T_SPRITE *Sprite_Create(char *ruta)
{
  struct T_SPRITE *sprite ;

  // Alojamos memoria para una estructura de tipo sprite
  sprite = (struct T_SPRITE *) malloc(sizeof(struct T_SPRITE)) ;

  // Llenamos la memoria alojada con 0s
  memset(sprite, 0, sizeof(struct T_SPRITE)) ;

  // Por defecto cada frame dura... Un frame :-)
  sprite->velocidad_animacion = 1.0f ;
  
  Sprite_SetScale(sprite, 1.0f) ;

  if(ruta == SPRITE_WILL_BE_ANIMATED) {
  
    // Si recibimos un NULL es porque queremos un sprite "vacío" para ponerle luego animaciones,
    // y no hace falta hacer nada más aquí
  }
  else {

    // Si no es NULL, creamos un frame para contener la imagen que toque
    sprite->frame_actual = Sprites_CreateFrame(ruta) ;
  }

  // Devolvemos el puntero al sprite
  return sprite ;
}




// ------------------------------------------------------------------------------------------------
// Borra un sprite y libera todos los recursos que hubiese podido alojar
//
void Sprite_Delete(struct T_SPRITE *sprite)
{
  // Nos aseguramos de que el puntero no es nulo

  ASSERT(sprite) ;

  if(sprite->animacion == NULL) {

    // Si el sprite no tiene animación es que sólo tiene su frame actual
  
    Sprites_ReleaseFrame(sprite->frame_actual) ;
  }
  else {

    // Si el sprite tiene animación no hacemos nada más, porque las animaciones se tienen que liberar a mano
  }

  // Liberamos la memoria que habíamos cogido para almacenar la estructura del sprite

  free(sprite) ;
}




// ------------------------------------------------------------------------------------------------
// Dibuja un sprite en las coordenadas especificadas
//
void Sprite_Draw(struct T_SPRITE *sprite, int x, int y)
{
  struct T_FRAME *frame ;

  // Nos aseguramos de que el vídeo está en marcha
  ASSERT(g_Video.renderer) ;

  // Nos aseguramos de que el sprite pasado como parámetro no es nulo
  ASSERT(sprite) ;

  // Si el sprite no tiene un frame que dibujar nos marchamos
  if(sprite->frame_actual == NULL) return ;
  if(sprite->frame_actual->surface == NULL) return ;

  // Usaremos esta variable para que el código quede un poco más corto y legible
  frame = sprite->frame_actual ;

  // Nos aseguramos de que el sprite tiene textura
  ASSERT(frame->texture) ;


  {
    // La SDL necesita que le especifiquemos un par de rectángulos en su formato para poder dibujar
    SDL_Rect srcrect ;
    SDL_Rect dstrect ;

    // Posición de la esquina superior izquierda
    srcrect.x = 0 ;
    srcrect.y = 0 ;

    // Número de píxels a leer
    srcrect.w = frame->tamx ;
    srcrect.h = frame->tamy ;

    // Posición de la esquina superior izquierda al dibujar
    dstrect.x = x - (int)(frame->hx * sprite->scalex) ;
    dstrect.y = y - (int)(frame->hy * sprite->scaley) ;

    // Tamaño visible al dibujar
    dstrect.w = (int)(frame->tamx * sprite->scalex) ;
    dstrect.h = (int)(frame->tamy * sprite->scaley) ;

    // Con todos estos datos ya podemos decirle que dibuje
    SDL_RenderCopy(g_Video.renderer, frame->texture, &srcrect, &dstrect) ;
  }
}




// ------------------------------------------------------------------------------------------------
//
//
void Sprite_SetAnimation(struct T_SPRITE *sprite, struct T_ANIMATION *anim, int bOverWrite)
{
  ASSERT(sprite) ;
  ASSERT(anim) ;

  // No podemos permitir que si el sprite está gestionando un frame por su cuenta se pierda en el limbo.

  // Si la animacion es NULL el frame actual no puede serlo
  
  if(sprite->animacion == NULL) {
    
    ASSERT(sprite->frame_actual == NULL) ; 
  }

  if(bOverWrite || anim != sprite->animacion) {

      sprite->animacion = anim ;

      sprite->frame_actual = anim->frames[0] ;
      sprite->num_frame_actual = 0 ;

      sprite->posicion_animacion = 0 ;

      sprite->animacion_completada = 0 ;
    }
}



// ------------------------------------------------------------------------------------------------
//
//
void Sprite_SetFrame(struct T_SPRITE *sprite, int num_frame)
{
  ASSERT(sprite) ;

  if(num_frame < 0) num_frame = 0 ;
  if(num_frame >= sprite->animacion->num_frames) num_frame = sprite->animacion->num_frames - 1 ;

  sprite->num_frame_actual = num_frame ;
  sprite->posicion_animacion = 0 ;
}



// ------------------------------------------------------------------------------------------------
//
//
void Sprite_Tick(struct T_SPRITE *sprite)
{
  struct T_ANIMATION *animacion ;
  
  ASSERT(sprite) ;

  animacion = sprite->animacion ;
  if(animacion == NULL) return ;

  sprite->posicion_animacion += sprite->velocidad_animacion ;

  while(sprite->posicion_animacion >= animacion->frames[sprite->num_frame_actual]->duracion) {
  
    sprite->posicion_animacion -= animacion->frames[sprite->num_frame_actual]->duracion ;
    sprite->num_frame_actual++ ;

    if(sprite->num_frame_actual >= animacion->num_frames) {

      sprite->animacion_completada = 1 ;

      if(animacion->tiene_loop) sprite->num_frame_actual = 0 ;
      else sprite->num_frame_actual = animacion->num_frames - 1 ;
    }
  }

  sprite->frame_actual = animacion->frames[sprite->num_frame_actual] ;
}




// ------------------------------------------------------------------------------------------------
//
//
struct T_FRAME *Sprites_CreateFrame(char *ruta)
{
  int bpp, pitchx_bytes, pitchx_pixels, pitchy_pixels ;
  struct T_FRAME *frame ;

  ASSERT(ruta) ;

  frame = (struct T_FRAME *) malloc(sizeof(struct T_FRAME)) ;

  if(frame != NULL) {

    memset(frame, 0, sizeof(struct T_FRAME)) ;

    // Pedimos a la rutina de carga de PNG que lea el fichero de la ruta pasada como parámetro, aloje memoria para
    // los píxels, la llene con la imagen y nos rellene las variables de tamaños del sprite
    frame->pixels = (unsigned long *) read_png_file(ruta, &bpp, &frame->tamx, &frame->tamy, &pitchx_bytes, &pitchx_pixels, &pitchy_pixels) ;

    if(frame->pixels != NULL) {

      // Si la cosa ha salido bien pedimos a la SDL que le diga al hardware que vamos a usar estos píxels para dibujar
      frame->surface = SDL_CreateRGBSurfaceFrom(frame->pixels,
                                                frame->tamx, frame->tamy,
                                                32,
                                                frame->tamx * 4,
                                                VIDEO_MASCARA_R, VIDEO_MASCARA_G, VIDEO_MASCARA_B, VIDEO_MASCARA_A
                                               ) ;

      // Creamos el handle de textura de hardware
      frame->texture = SDL_CreateTextureFromSurface(g_Video.renderer, frame->surface) ;

      // Indicamos al hardware de que este sprite va a necesitar cálculos de alpha blending (para que no se vea el rectángulo donde no hay dibujo)
      SDL_SetTextureBlendMode(frame->texture, SDL_BLENDMODE_BLEND) ;
    }
  }

  return frame ;
}




// ------------------------------------------------------------------------------------------------
//
//
void Sprites_ReleaseFrame(struct T_FRAME *frame)
{
  // Si el frame tiene un handle de textura pedimos al hardware que se olvide de la imagen y 
  // libere la memoria y los handles que haya podido alojar
  if(frame->texture) SDL_DestroyTexture(frame->texture) ;

  // Si el frame tiene una surface de SDL la liberamos
  if(frame->surface) SDL_FreeSurface(frame->surface) ;

  // Si el frame alojó el buffer para almacenar sus píxels liberamos la memoria
  if(frame->pixels != NULL) free(frame->pixels) ;
}




// ------------------------------------------------------------------------------------------------
//
//
struct T_ANIMATION *Sprites_CreateAnimation(struct T_DESCRIPCION_ANIMACION *descripcion_anim)
{
  struct T_DESCRIPCION_FRAME_ANIMACION *descripcion_frame ;
  struct T_ANIMATION *anim ;
  int var_frame ;

  ASSERT(descripcion_anim) ;

  anim = (struct T_ANIMATION *) malloc(sizeof(struct T_ANIMATION)) ;
  
  anim->frames = (struct T_FRAME **) malloc(descripcion_anim->num_frames * sizeof(struct T_FRAME *)) ;
  anim->num_frames = descripcion_anim->num_frames ;
  anim->tiene_loop = descripcion_anim->modo_loop ;

  for(var_frame = 0; var_frame < descripcion_anim->num_frames; var_frame++) {

    descripcion_frame = descripcion_anim->descripcion_frames[var_frame] ;

    anim->frames[var_frame] = Sprites_CreateFrame(descripcion_frame->ruta) ;

    anim->frames[var_frame]->duracion = descripcion_frame->duracion ;
    anim->frames[var_frame]->hx       = descripcion_frame->hx ;
    anim->frames[var_frame]->hy       = descripcion_frame->hy ;
  }

  return anim ;
}




// ------------------------------------------------------------------------------------------------
//
//
void Sprites_ReleaseAnimation(struct T_ANIMATION *anim)
{
  int var_frame ;

  ASSERT(anim) ;

  for(var_frame = 0; var_frame < anim->num_frames; var_frame++) {

    Sprites_ReleaseFrame(anim->frames[var_frame]) ;
  }

  free(anim) ;
}




// ------------------------------------------------------------------------------------------------
// Escala el tamaño del sprite por el factor indicado
//
void Sprite_SetScale(struct T_SPRITE *sprite, float scale)
{
  ASSERT(sprite) ;

  if(scale < 0.0f) scale = 0.0f ;

  sprite->scalex = scale ;
  sprite->scaley = scale ;
}




// ------------------------------------------------------------------------------------------------
// Escala el tamaño horizontal del sprite por el factor indicado
//
void Sprite_SetScaleX(struct T_SPRITE *sprite, float scalex)
{
  ASSERT(sprite) ;

  if(scalex < 0.0f) scalex = 0.0f ;

  sprite->scalex = scalex ;
}




// ------------------------------------------------------------------------------------------------
// Escala el tamaño vertical del sprite por el factor indicado
//
void Sprite_SetScaleY(struct T_SPRITE *sprite, float scaley)
{
  ASSERT(sprite) ;

  if(scaley < 0.0f) scaley = 0.0f ;

  sprite->scaley = scaley ;
}




// ------------------------------------------------------------------------------------------------
//
//
void Sprite_SetAnimationSpeed(struct T_SPRITE *sprite, float speed)
{
  sprite->velocidad_animacion = speed ;
}
