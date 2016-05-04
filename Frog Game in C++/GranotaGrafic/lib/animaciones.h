#ifndef __ANIMACIONES_INCLUDED_
#define __ANIMACIONES_INCLUDED_

#include "lib/libreria.h"


// Animaciones de los Nerds

// Nerd 1

extern struct T_DESCRIPCION_ANIMACION animacion_nerd1_standing ;           // Estar quieto
extern struct T_DESCRIPCION_ANIMACION animacion_nerd1_shooting ;           // Disparar
extern struct T_DESCRIPCION_ANIMACION animacion_nerd1_hit ;                // Recibir golpe
extern struct T_DESCRIPCION_ANIMACION animacion_nerd1_death ;              // Morir
extern struct T_DESCRIPCION_ANIMACION animacion_nerd1_walk ;               // Caminar
extern struct T_DESCRIPCION_ANIMACION animacion_nerd1_brag ;               // Chulear

// Faltan: Walking y Vacileta


// Animaciones de los Zombies

// Zombie 1

struct T_DESCRIPCION_ANIMACION animacion_zombie1_walk ;                    // Caminar
struct T_DESCRIPCION_ANIMACION animacion_zombie1_walk_injured ;            // Caminar con el cerebro al aire
struct T_DESCRIPCION_ANIMACION animacion_zombie1_hit ;                     // Recibir golpe
struct T_DESCRIPCION_ANIMACION animacion_zombie1_death ;                   // Morir


// Animaciones de los disparos

// Disparo 1

extern struct T_DESCRIPCION_ANIMACION animacion_disparo_bird ;             // Disparo bird


// Animaciones de efectos

// Sangre de Zombie

extern struct T_DESCRIPCION_ANIMACION animacion_sangre_zombie ;            // Sangre de zombie

// Falta: Sangre de Nerd

// Varios

extern struct T_DESCRIPCION_ANIMACION animacion_pantalla_titulo ;          // Pantalla de título
extern struct T_DESCRIPCION_ANIMACION animacion_numeros ;                  // Números para el HUD
extern struct T_DESCRIPCION_ANIMACION animacion_playdude ;                 // PlayDude

#endif
