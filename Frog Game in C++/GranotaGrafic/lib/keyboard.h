#ifndef __KEYBOARD_INCLUDED_
#define __KEYBOARD_INCLUDED_

#include <SDL.h>
#include "keyboard_sdl.h"


// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------

struct T_KEYBOARD
{
  int cnt[NUM_KEYBOARD_KEY_CODES] ;              // Indica si la tecla está físicamente pulsada
  int trg[NUM_KEYBOARD_KEY_CODES] ;              // Indica si la tecla ha sido pulsada este frame
} ;


// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------

void Keyboard_ProcessKeyDown(int tecla) ;
void Keyboard_ProcessKeyUp(int tecla) ;
void Keyboard_Init() ;
void Keyboard_Tick() ;

// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------

//extern struct T_KEYBOARD g_Keyboard ;
int Keyboard_GetKeyCnt(int cual) ;
int Keyboard_GetKeyTrg(int cual) ;

#endif
