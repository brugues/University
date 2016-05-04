#include "libreria.h"


// ------------------------------------------------------------------------------------------------
//                                Nerd1, animación de standing
// ------------------------------------------------------------------------------------------------

struct T_DESCRIPCION_FRAME_ANIMACION nerd1_standing_0000 = {

  20,                                       // int duracion ;

  34,                                      // int hx ;
  97,                                      // int hy ;

  "data/nerd1/nerd_standing/nerd0000.png"  // char *ruta ;
} ;

struct T_DESCRIPCION_FRAME_ANIMACION nerd1_standing_0001 = {

  20,                                       // int duracion ;

  34,                                      // int hx ;
  97,                                      // int hy ;

  "data/nerd1/nerd_standing/nerd0001.png"  // char *ruta ;
} ;

struct T_DESCRIPCION_FRAME_ANIMACION nerd1_standing_0002 = {

  20,                                       // int duracion ;

  34,                                      // int hx ;
  97,                                      // int hy ;

  "data/nerd1/nerd_standing/nerd0002.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_ANIMACION animacion_nerd1_standing = {

  // int modo_loop ;

  SPRITES_LOOP_ON,

  //! Número de frames de la animación

  3,

  // struct T_DESCRIPCION_FRAME_ANIMACION *descripcion_frames ;

  {
    &nerd1_standing_0000,
    &nerd1_standing_0001,
    &nerd1_standing_0002,
  }
} ;





// ------------------------------------------------------------------------------------------------
//                                Nerd1, animación de disparar
// ------------------------------------------------------------------------------------------------

struct T_DESCRIPCION_FRAME_ANIMACION nerd1_shooting_0000 = {

  3,                                             // int duracion ;

  33,                                            // int hx ;
  97,                                            // int hy ;

  "data/nerd1/nerd_shooting/nerd_shoot0000.png"  // char *ruta ;
} ;

struct T_DESCRIPCION_FRAME_ANIMACION nerd1_shooting_0001 = {

  3,                                             // int duracion ;

  33,                                            // int hx ;
  97,                                            // int hy ;

  "data/nerd1/nerd_shooting/nerd_shoot0001.png"  // char *ruta ;
} ;

struct T_DESCRIPCION_FRAME_ANIMACION nerd1_shooting_0002 = {

  3,                                             // int duracion ;

  33,                                            // int hx ;
  97,                                            // int hy ;

  "data/nerd1/nerd_shooting/nerd_shoot0002.png"  // char *ruta ;
} ;

struct T_DESCRIPCION_FRAME_ANIMACION nerd1_shooting_0003 = {

  3,                                             // int duracion ;

  33,                                            // int hx ;
  97,                                            // int hy ;

  "data/nerd1/nerd_shooting/nerd_shoot0003.png"  // char *ruta ;
} ;

struct T_DESCRIPCION_FRAME_ANIMACION nerd1_shooting_0004 = {

  3,                                             // int duracion ;

  33,                                            // int hx ;
  97,                                            // int hy ;

  "data/nerd1/nerd_shooting/nerd_shoot0004.png"  // char *ruta ;
} ;

struct T_DESCRIPCION_FRAME_ANIMACION nerd1_shooting_0005 = {

  3,                                             // int duracion ;

  33,                                            // int hx ;
  97,                                            // int hy ;

  "data/nerd1/nerd_shooting/nerd_shoot0005.png"  // char *ruta ;
} ;

struct T_DESCRIPCION_FRAME_ANIMACION nerd1_shooting_0006 = {

  3,                                             // int duracion ;

  33,                                            // int hx ;
  97,                                            // int hy ;

  "data/nerd1/nerd_shooting/nerd_shoot0006.png"  // char *ruta ;
} ;

struct T_DESCRIPCION_FRAME_ANIMACION nerd1_shooting_0007 = {

  3,                                             // int duracion ;

  33,                                            // int hx ;
  97,                                            // int hy ;

  "data/nerd1/nerd_shooting/nerd_shoot0007.png"  // char *ruta ;
} ;

struct T_DESCRIPCION_FRAME_ANIMACION nerd1_shooting_0008 = {

  3,                                             // int duracion ;

  33,                                            // int hx ;
  97,                                            // int hy ;

  "data/nerd1/nerd_shooting/nerd_shoot0008.png"  // char *ruta ;
} ;

struct T_DESCRIPCION_FRAME_ANIMACION nerd1_shooting_0009 = {

  3,                                             // int duracion ;

  33,                                            // int hx ;
  97,                                            // int hy ;

  "data/nerd1/nerd_shooting/nerd_shoot0009.png"  // char *ruta ;
} ;

struct T_DESCRIPCION_FRAME_ANIMACION nerd1_shooting_0010 = {

  3,                                             // int duracion ;

  33,                                            // int hx ;
  97,                                            // int hy ;

  "data/nerd1/nerd_shooting/nerd_shoot0010.png"  // char *ruta ;
} ;

struct T_DESCRIPCION_FRAME_ANIMACION nerd1_shooting_0011 = {

  3,                                             // int duracion ;

  33,                                            // int hx ;
  97,                                            // int hy ;

  "data/nerd1/nerd_shooting/nerd_shoot0011.png"  // char *ruta ;
} ;

struct T_DESCRIPCION_FRAME_ANIMACION nerd1_shooting_0012 = {

  3,                                             // int duracion ;

  33,                                            // int hx ;
  97,                                            // int hy ;

  "data/nerd1/nerd_shooting/nerd_shoot0012.png"  // char *ruta ;
} ;

struct T_DESCRIPCION_FRAME_ANIMACION nerd1_shooting_0013 = {

  3,                                             // int duracion ;

  33,                                            // int hx ;
  97,                                            // int hy ;

  "data/nerd1/nerd_shooting/nerd_shoot0013.png"  // char *ruta ;
} ;

struct T_DESCRIPCION_FRAME_ANIMACION nerd1_shooting_0014 = {

  3,                                             // int duracion ;

  33,                                            // int hx ;
  97,                                            // int hy ;

  "data/nerd1/nerd_shooting/nerd_shoot0014.png"  // char *ruta ;
} ;

struct T_DESCRIPCION_FRAME_ANIMACION nerd1_shooting_0015 = {

  3,                                             // int duracion ;

  33,                                            // int hx ;
  97,                                            // int hy ;

  "data/nerd1/nerd_shooting/nerd_shoot0015.png"  // char *ruta ;
} ;

struct T_DESCRIPCION_FRAME_ANIMACION nerd1_shooting_0016 = {

  3,                                             // int duracion ;

  33,                                            // int hx ;
  97,                                            // int hy ;

  "data/nerd1/nerd_shooting/nerd_shoot0016.png"  // char *ruta ;
} ;

struct T_DESCRIPCION_FRAME_ANIMACION nerd1_shooting_0017 = {

  3,                                             // int duracion ;

  33,                                            // int hx ;
  97,                                            // int hy ;

  "data/nerd1/nerd_shooting/nerd_shoot0017.png"  // char *ruta ;
} ;

struct T_DESCRIPCION_FRAME_ANIMACION nerd1_shooting_0018 = {

  3,                                             // int duracion ;

  33,                                            // int hx ;
  97,                                            // int hy ;

  "data/nerd1/nerd_shooting/nerd_shoot0018.png"  // char *ruta ;
} ;

struct T_DESCRIPCION_FRAME_ANIMACION nerd1_shooting_0019 = {

  3,                                             // int duracion ;

  33,                                            // int hx ;
  97,                                            // int hy ;

  "data/nerd1/nerd_shooting/nerd_shoot0019.png"  // char *ruta ;
} ;

struct T_DESCRIPCION_FRAME_ANIMACION nerd1_shooting_0020 = {

  3,                                             // int duracion ;

  33,                                            // int hx ;
  97,                                            // int hy ;

  "data/nerd1/nerd_shooting/nerd_shoot0020.png"  // char *ruta ;
} ;

struct T_DESCRIPCION_FRAME_ANIMACION nerd1_shooting_0021 = {

  3,                                             // int duracion ;

  33,                                            // int hx ;
  97,                                            // int hy ;

  "data/nerd1/nerd_shooting/nerd_shoot0021.png"  // char *ruta ;
} ;

struct T_DESCRIPCION_FRAME_ANIMACION nerd1_shooting_0022 = {

  3,                                             // int duracion ;

  33,                                            // int hx ;
  97,                                            // int hy ;

  "data/nerd1/nerd_shooting/nerd_shoot0022.png"  // char *ruta ;
} ;

struct T_DESCRIPCION_FRAME_ANIMACION nerd1_shooting_0023 = {

  3,                                             // int duracion ;

  33,                                            // int hx ;
  97,                                            // int hy ;

  "data/nerd1/nerd_shooting/nerd_shoot0023.png"  // char *ruta ;
} ;

struct T_DESCRIPCION_FRAME_ANIMACION nerd1_shooting_0024 = {

  3,                                             // int duracion ;

  33,                                            // int hx ;
  97,                                            // int hy ;

  "data/nerd1/nerd_shooting/nerd_shoot0024.png"  // char *ruta ;
} ;

struct T_DESCRIPCION_FRAME_ANIMACION nerd1_shooting_0025 = {

  3,                                             // int duracion ;

  33,                                            // int hx ;
  97,                                            // int hy ;

  "data/nerd1/nerd_shooting/nerd_shoot0025.png"  // char *ruta ;
} ;

struct T_DESCRIPCION_FRAME_ANIMACION nerd1_shooting_0026 = {

  3,                                             // int duracion ;

  33,                                            // int hx ;
  97,                                            // int hy ;

  "data/nerd1/nerd_shooting/nerd_shoot0026.png"  // char *ruta ;
} ;

struct T_DESCRIPCION_FRAME_ANIMACION nerd1_shooting_0027 = {

  3,                                             // int duracion ;

  33,                                            // int hx ;
  97,                                            // int hy ;

  "data/nerd1/nerd_shooting/nerd_shoot0027.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_ANIMACION animacion_nerd1_shooting = {

  // int modo_loop ;

  SPRITES_LOOP_OFF,

  //! Número de frames de la animación

  28,

  // struct T_DESCRIPCION_FRAME_ANIMACION *descripcion_frames ;

  {
    &nerd1_shooting_0000,
    &nerd1_shooting_0001,
    &nerd1_shooting_0002,
    &nerd1_shooting_0003,
    &nerd1_shooting_0004,
    &nerd1_shooting_0005,
    &nerd1_shooting_0006,
    &nerd1_shooting_0007,
    &nerd1_shooting_0008,
    &nerd1_shooting_0009,
    &nerd1_shooting_0010,
    &nerd1_shooting_0011,
    &nerd1_shooting_0012,
    &nerd1_shooting_0013,
    &nerd1_shooting_0014,
    &nerd1_shooting_0015,
    &nerd1_shooting_0016,
    &nerd1_shooting_0017,
    &nerd1_shooting_0018,
    &nerd1_shooting_0019,
    &nerd1_shooting_0020,
    &nerd1_shooting_0021,
    &nerd1_shooting_0022,
    &nerd1_shooting_0023,
    &nerd1_shooting_0024,
    &nerd1_shooting_0025,
    &nerd1_shooting_0026,
    &nerd1_shooting_0027
  }
} ;





// ------------------------------------------------------------------------------------------------
//                              Nerd1, animación de recibir golpe
// ------------------------------------------------------------------------------------------------


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_hit_0000 = {

  50,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_hit/nerd_hit0000.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_hit_0001 = {

  50,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_hit/nerd_hit0001.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_hit_0002 = {
   
  50,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_hit/nerd_hit0002.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_hit_0003 = {

  50,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_hit/nerd_hit0003.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_hit_0004 = {

  50,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_hit/nerd_hit0004.png"  // char *ruta ;
} ;




struct T_DESCRIPCION_ANIMACION animacion_nerd1_hit = {

  // int modo_loop ;

  SPRITES_LOOP_OFF,

  //! Número de frames de la animación

  5,

  // struct T_DESCRIPCION_FRAME_ANIMACION *descripcion_frames ;

  {
    &nerd1_hit_0000,
    &nerd1_hit_0001,
    &nerd1_hit_0002,
    &nerd1_hit_0003,
    &nerd1_hit_0004
  }
} ;




// ------------------------------------------------------------------------------------------------
//                                  Nerd1, animación de morir
// ------------------------------------------------------------------------------------------------


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0000 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0000.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0001 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0001.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0002 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0002.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0003 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0003.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0004 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0004.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0005 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0005.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0006 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0006.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0007 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0007.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0008 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0008.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0009 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0009.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0010 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0010.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0011 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0011.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0012 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0012.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0013 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0013.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0014 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0014.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0015 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0015.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0016 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0016.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0017 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0017.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0018 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0018.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0019 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0019.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0020 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0020.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0021 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0021.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0022 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0022.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0023 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0023.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0024 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0024.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0025 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0025.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0026 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0026.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0027 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0027.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0028 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0028.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0029 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0029.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0030 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0030.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0031 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0031.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0032 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0032.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_death_0033 = {

  4,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_disintegration/nerd_disintegration0033.png"  // char *ruta ;
} ;




struct T_DESCRIPCION_ANIMACION animacion_nerd1_death = {

  // int modo_loop ;

  SPRITES_LOOP_ON,

  //! Número de frames de la animación

  34,

  // struct T_DESCRIPCION_FRAME_ANIMACION *descripcion_frames ;

  {
    &nerd1_death_0000,
    &nerd1_death_0001,
    &nerd1_death_0002,
    &nerd1_death_0003,
    &nerd1_death_0004,
    &nerd1_death_0005,
    &nerd1_death_0006,
    &nerd1_death_0007,
    &nerd1_death_0008,
    &nerd1_death_0009,
    &nerd1_death_0010,
    &nerd1_death_0011,
    &nerd1_death_0012,
    &nerd1_death_0013,
    &nerd1_death_0014,
    &nerd1_death_0015,
    &nerd1_death_0016,
    &nerd1_death_0017,
    &nerd1_death_0018,
    &nerd1_death_0019,
    &nerd1_death_0020,
    &nerd1_death_0021,
    &nerd1_death_0022,
    &nerd1_death_0023,
    &nerd1_death_0024,
    &nerd1_death_0025,
    &nerd1_death_0026,
    &nerd1_death_0027,
    &nerd1_death_0028,
    &nerd1_death_0029,
    &nerd1_death_0030,
    &nerd1_death_0031,
    &nerd1_death_0032,
    &nerd1_death_0033
  }
} ;





// ------------------------------------------------------------------------------------------------
//                                 Nerd1, animación de caminar
// ------------------------------------------------------------------------------------------------


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_walk_0000 = {

  6,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_walking/nerd_walk0000.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_walk_0001 = {

  6,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_walking/nerd_walk0001.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_walk_0002 = {
   
  6,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_walking/nerd_walk0002.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_walk_0003 = {

  6,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_walking/nerd_walk0003.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_walk_0004 = {

  6,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_walking/nerd_walk0004.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_walk_0005 = {

  6,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_walking/nerd_walk0005.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_walk_0006 = {

  6,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_walking/nerd_walk0006.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_walk_0007 = {

  6,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_walking/nerd_walk0007.png"  // char *ruta ;
} ;




struct T_DESCRIPCION_ANIMACION animacion_nerd1_walk = {

  // int modo_loop ;

  SPRITES_LOOP_ON,

  //! Número de frames de la animación

  8,

  // struct T_DESCRIPCION_FRAME_ANIMACION *descripcion_frames ;

  {
    &nerd1_walk_0000,
    &nerd1_walk_0001,
    &nerd1_walk_0002,
    &nerd1_walk_0003,
    &nerd1_walk_0004,
    &nerd1_walk_0005,
    &nerd1_walk_0006,
    &nerd1_walk_0007
  }
} ;









// ------------------------------------------------------------------------------------------------
//                              Nerd1, animación de recibir golpe
// ------------------------------------------------------------------------------------------------


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_brag_0000 = {

  6,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_vacileta/nerd0003.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_brag_0001 = {

  6,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_vacileta/nerd0004.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_brag_0002 = {
   
  6,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_vacileta/nerd0005.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_brag_0003 = {

  6,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_vacileta/nerd0006.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_brag_0004 = {

  6,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_vacileta/nerd0007.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_brag_0005 = {

  6,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_vacileta/nerd0008.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_brag_0006 = {

  6,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_vacileta/nerd0009.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_brag_0007 = {

  6,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_vacileta/nerd0010.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION nerd1_brag_0008 = {

  6,                                             // int duracion ;

  120,                                           // int hx ;
  246,                                           // int hy ;

  "data/nerd1/nerd_vacileta/nerd0011.png"  // char *ruta ;
} ;




struct T_DESCRIPCION_ANIMACION animacion_nerd1_brag = {

  // int modo_loop ;

  SPRITES_LOOP_OFF,

  //! Número de frames de la animación

  9,

  // struct T_DESCRIPCION_FRAME_ANIMACION *descripcion_frames ;

  {
    &nerd1_brag_0000,
    &nerd1_brag_0001,
    &nerd1_brag_0002,
    &nerd1_brag_0003,
    &nerd1_brag_0004,
    &nerd1_brag_0005,
    &nerd1_brag_0006,
    &nerd1_brag_0007,
    &nerd1_brag_0008
  }
} ;






























// ------------------------------------------------------------------------------------------------
//                                      Disparo bird
// ------------------------------------------------------------------------------------------------


struct T_DESCRIPCION_FRAME_ANIMACION disparo_bird_0000 = {

  4,                                            // int duracion ;

  11,                                           // int hx ;
  11,                                           // int hy ;

  "data/disparo_bird/disparo_bird0000.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION disparo_bird_0001 = {

  4,                                            // int duracion ;

  11,                                           // int hx ;
  11,                                           // int hy ;

  "data/disparo_bird/disparo_bird0001.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION disparo_bird_0002 = {

  4,                                            // int duracion ;

  11,                                           // int hx ;
  11,                                           // int hy ;

  "data/disparo_bird/disparo_bird0002.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION disparo_bird_0003 = {

  4,                                            // int duracion ;

  11,                                           // int hx ;
  11,                                           // int hy ;

  "data/disparo_bird/disparo_bird0003.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION disparo_bird_0004 = {

  4,                                            // int duracion ;

  11,                                           // int hx ;
  11,                                           // int hy ;

  "data/disparo_bird/disparo_bird0004.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION disparo_bird_0005 = {

  4,                                            // int duracion ;

  11,                                           // int hx ;
  11,                                           // int hy ;

  "data/disparo_bird/disparo_bird0005.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION disparo_bird_0006 = {

  4,                                            // int duracion ;

  11,                                           // int hx ;
  11,                                           // int hy ;

  "data/disparo_bird/disparo_bird0006.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION disparo_bird_0007 = {

  4,                                            // int duracion ;

  11,                                           // int hx ;
  11,                                           // int hy ;

  "data/disparo_bird/disparo_bird0007.png"  // char *ruta ;
} ;




struct T_DESCRIPCION_ANIMACION animacion_disparo_bird = {

  // int modo_loop ;

  SPRITES_LOOP_ON,

  //! Número de frames de la animación

  8,

  // struct T_DESCRIPCION_FRAME_ANIMACION *descripcion_frames ;

  {
    &disparo_bird_0000,
    &disparo_bird_0001,
    &disparo_bird_0002,
    &disparo_bird_0003,
    &disparo_bird_0004,
    &disparo_bird_0005,
    &disparo_bird_0006,
    &disparo_bird_0007
  }
} ;















// ------------------------------------------------------------------------------------------------
//                                Zombie 1, animación de caminar
// ------------------------------------------------------------------------------------------------


struct T_DESCRIPCION_FRAME_ANIMACION zombie1_walk_0000 = {

  11,                                            // int duracion ;

  45,                                           // int hx ;
  97,                                           // int hy ;

  "data/zombie1/walk/zombie1_walk0000.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION zombie1_walk_0001 = {

  11,                                            // int duracion ;

  45,                                           // int hx ;
  97,                                           // int hy ;

  "data/zombie1/walk/zombie1_walk0001.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION zombie1_walk_0002 = {

  11,                                            // int duracion ;

  45,                                           // int hx ;
  97,                                           // int hy ;

  "data/zombie1/walk/zombie1_walk0002.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION zombie1_walk_0003 = {

  11,                                            // int duracion ;

  45,                                           // int hx ;
  97,                                           // int hy ;

  "data/zombie1/walk/zombie1_walk0003.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_ANIMACION animacion_zombie1_walk = {

  // int modo_loop ;

  SPRITES_LOOP_ON,

  //! Número de frames de la animación

  4,

  // struct T_DESCRIPCION_FRAME_ANIMACION *descripcion_frames ;

  {
    &zombie1_walk_0000,
    &zombie1_walk_0001,
    &zombie1_walk_0002,
    &zombie1_walk_0003
  }
} ;


// ------------------------------------------------------------------------------------------------
//                   Zombie 1, animación de caminar con el cerebro al aire
// ------------------------------------------------------------------------------------------------


struct T_DESCRIPCION_FRAME_ANIMACION zombie1_walk_injured_0000 = {

  11,                                            // int duracion ;

  45,                                           // int hx ;
  97,                                           // int hy ;

  "data/zombie1/walk_injured/zombie_walk_iinjured0000.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION zombie1_walk_injured_0001 = {

  11,                                            // int duracion ;

  45,                                           // int hx ;
  97,                                           // int hy ;

  "data/zombie1/walk_injured/zombie_walk_iinjured0001.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION zombie1_walk_injured_0002 = {

  11,                                            // int duracion ;

  45,                                           // int hx ;
  97,                                           // int hy ;

  "data/zombie1/walk_injured/zombie_walk_iinjured0002.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION zombie1_walk_injured_0003 = {

  11,                                            // int duracion ;

  45,                                           // int hx ;
  97,                                           // int hy ;

  "data/zombie1/walk_injured/zombie_walk_iinjured0003.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_ANIMACION animacion_zombie1_walk_injured = {

  // int modo_loop ;

  SPRITES_LOOP_ON,

  //! Número de frames de la animación

  4,

  // struct T_DESCRIPCION_FRAME_ANIMACION *descripcion_frames ;

  {
    &zombie1_walk_injured_0000,
    &zombie1_walk_injured_0001,
    &zombie1_walk_injured_0002,
    &zombie1_walk_injured_0003
  }
} ;



// ------------------------------------------------------------------------------------------------
//                          Zombie 1, animación de recibir golpe
// ------------------------------------------------------------------------------------------------


struct T_DESCRIPCION_FRAME_ANIMACION zombie1_hit_0000 = {

  11,                                           // int duracion ;

  45,                                           // int hx ;
  97,                                           // int hy ;

  "data/zombie1/hit/zombie_hit0000.png"         // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION zombie1_hit_0001 = {

  11,                                            // int duracion ;

  45,                                           // int hx ;
  97,                                           // int hy ;

  "data/zombie1/hit/zombie_hit0001.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION zombie1_hit_0002 = {

  11,                                            // int duracion ;

  45,                                           // int hx ;
  97,                                           // int hy ;

  "data/zombie1/hit/zombie_hit0002.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION zombie1_hit_0003 = {

  11,                                            // int duracion ;

  45,                                           // int hx ;
  97,                                           // int hy ;

  "data/zombie1/hit/zombie_hit0003.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_ANIMACION animacion_zombie1_hit = {

  // int modo_loop ;

  SPRITES_LOOP_ON,

  //! Número de frames de la animación

  4,

  // struct T_DESCRIPCION_FRAME_ANIMACION *descripcion_frames ;

  {
    &zombie1_hit_0000,
    &zombie1_hit_0001,
    &zombie1_hit_0002,
    &zombie1_hit_0003
  }
} ;



// ------------------------------------------------------------------------------------------------
//                               Zombie 1, animación de morir
// ------------------------------------------------------------------------------------------------

struct T_DESCRIPCION_FRAME_ANIMACION zombie1_death_0000 = {

  11,                                           // int duracion ;

  45,                                           // int hx ;
  97,                                           // int hy ;

  "data/zombie1/disintegration/zombie_disintegration0000.png"         // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION zombie1_death_0001 = {

  11,                                            // int duracion ;

  45,                                           // int hx ;
  97,                                           // int hy ;

  "data/zombie1/disintegration/zombie_disintegration0001.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION zombie1_death_0002 = {

  11,                                            // int duracion ;

  45,                                           // int hx ;
  97,                                           // int hy ;

  "data/zombie1/disintegration/zombie_disintegration0002.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION zombie1_death_0003 = {

  11,                                            // int duracion ;

  45,                                           // int hx ;
  97,                                           // int hy ;

  "data/zombie1/disintegration/zombie_disintegration0003.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION zombie1_death_0004 = {

  11,                                            // int duracion ;

  45,                                           // int hx ;
  97,                                           // int hy ;

  "data/zombie1/disintegration/zombie_disintegration0004.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION zombie1_death_0005 = {

  11,                                            // int duracion ;

  45,                                           // int hx ;
  97,                                           // int hy ;

  "data/zombie1/disintegration/zombie_disintegration0005.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION zombie1_death_0006 = {

  11,                                            // int duracion ;

  45,                                           // int hx ;
  97,                                           // int hy ;

  "data/zombie1/disintegration/zombie_disintegration0006.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION zombie1_death_0007 = {

  11,                                            // int duracion ;

  45,                                           // int hx ;
  97,                                           // int hy ;

  "data/zombie1/disintegration/zombie_disintegration0007.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_ANIMACION animacion_zombie1_death = {

  // int modo_loop ;

  SPRITES_LOOP_ON,

  //! Número de frames de la animación

  8,

  // struct T_DESCRIPCION_FRAME_ANIMACION *descripcion_frames ;

  {
    &zombie1_death_0000,
    &zombie1_death_0001,
    &zombie1_death_0002,
    &zombie1_death_0003,
    &zombie1_death_0004,
    &zombie1_death_0005,
    &zombie1_death_0006,
    &zombie1_death_0007
  }
} ;










// ------------------------------------------------------------------------------------------------
//                                     Pantalla de título
// ------------------------------------------------------------------------------------------------

struct T_DESCRIPCION_FRAME_ANIMACION sangre_zombie_0000 = {

  6,                                      // int duracion ;

  58,                                     // int hx ;
  30,                                     // int hy ;

  "data/sangre hit/sangre hit20000.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION sangre_zombie_0001 = {

  6,                                      // int duracion ;

  58,                                     // int hx ;
  30,                                     // int hy ;

  "data/sangre hit/sangre hit20001.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION sangre_zombie_0002 = {

  6,                                      // int duracion ;

  58,                                     // int hx ;
  30,                                     // int hy ;

  "data/sangre hit/sangre hit20002.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION sangre_zombie_0003 = {

  6,                                      // int duracion ;

  58,                                     // int hx ;
  30,                                     // int hy ;

  "data/sangre hit/sangre hit20003.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION sangre_zombie_0004 = {

  6,                                      // int duracion ;

  58,                                     // int hx ;
  30,                                     // int hy ;

  "data/sangre hit/sangre hit20004.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION sangre_zombie_0005 = {

  6,                                      // int duracion ;

  58,                                     // int hx ;
  30,                                     // int hy ;

  "data/sangre hit/sangre hit20005.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION sangre_zombie_0006 = {

  6,                                      // int duracion ;

  58,                                     // int hx ;
  30,                                     // int hy ;

  "data/sangre hit/sangre hit20006.png"  // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION sangre_zombie_0007 = {

  6,                                      // int duracion ;

  58,                                     // int hx ;
  30,                                     // int hy ;

  "data/sangre hit/sangre hit20007.png"  // char *ruta ;
} ;



struct T_DESCRIPCION_ANIMACION animacion_sangre_zombie = {

  // int modo_loop ;

  SPRITES_LOOP_ON,

  //! Número de frames de la animación

  8,

  // struct T_DESCRIPCION_FRAME_ANIMACION *descripcion_frames ;

  {
    &sangre_zombie_0000,
    &sangre_zombie_0001,
    &sangre_zombie_0002,
    &sangre_zombie_0003,
    &sangre_zombie_0004,
    &sangre_zombie_0005,
    &sangre_zombie_0006,
    &sangre_zombie_0007,
  }
} ;












// ------------------------------------------------------------------------------------------------
//                                     Pantalla de título
// ------------------------------------------------------------------------------------------------

struct T_DESCRIPCION_FRAME_ANIMACION pantalla_titulo_0000 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/titulo/titulo0000.png"         // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION pantalla_titulo_0001 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/titulo/titulo001.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION pantalla_titulo_0002 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/titulo/titulo002.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION pantalla_titulo_0003 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/titulo/titulo003.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION pantalla_titulo_0004 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/titulo/titulo004.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION pantalla_titulo_0005 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/titulo/titulo005.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION pantalla_titulo_0006 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/titulo/titulo006.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION pantalla_titulo_0007 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/titulo/titulo007.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION pantalla_titulo_0008 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/titulo/titulo008.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION pantalla_titulo_0009 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/titulo/titulo009.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION pantalla_titulo_0010 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/titulo/titulo010.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION pantalla_titulo_0011 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/titulo/titulo011.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION pantalla_titulo_0012 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/titulo/titulo012.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION pantalla_titulo_0013 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/titulo/titulo013.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION pantalla_titulo_0014 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/titulo/titulo014.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION pantalla_titulo_0015 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/titulo/titulo015.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION pantalla_titulo_0016 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/titulo/titulo016.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION pantalla_titulo_0017 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/titulo/titulo017.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION pantalla_titulo_0018 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/titulo/titulo018.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION pantalla_titulo_0019 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/titulo/titulo019.png"           // char *ruta ;
} ;

struct T_DESCRIPCION_FRAME_ANIMACION pantalla_titulo_0020 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/titulo/titulo020.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION pantalla_titulo_0021 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/titulo/titulo021.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION pantalla_titulo_0022 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/titulo/titulo022.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION pantalla_titulo_0023 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/titulo/titulo023.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION pantalla_titulo_0024 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/titulo/titulo024.png"           // char *ruta ;
} ;





struct T_DESCRIPCION_ANIMACION animacion_pantalla_titulo = {

  // int modo_loop ;

  SPRITES_LOOP_OFF,

  //! Número de frames de la animación

  25,

  // struct T_DESCRIPCION_FRAME_ANIMACION *descripcion_frames ;

  {
    &pantalla_titulo_0000,
    &pantalla_titulo_0001,
    &pantalla_titulo_0002,
    &pantalla_titulo_0003,
    &pantalla_titulo_0004,
    &pantalla_titulo_0005,
    &pantalla_titulo_0006,
    &pantalla_titulo_0007,
    &pantalla_titulo_0008,
    &pantalla_titulo_0009,
    &pantalla_titulo_0010,
    &pantalla_titulo_0011,
    &pantalla_titulo_0012,
    &pantalla_titulo_0013,
    &pantalla_titulo_0014,
    &pantalla_titulo_0015,
    &pantalla_titulo_0016,
    &pantalla_titulo_0017,
    &pantalla_titulo_0018,
    &pantalla_titulo_0019,
    &pantalla_titulo_0020,
    &pantalla_titulo_0021,
    &pantalla_titulo_0022,
    &pantalla_titulo_0023,
    &pantalla_titulo_0024
  }
} ;



// ------------------------------------------------------------------------------------------------
//                                     Números para el HUD
// ------------------------------------------------------------------------------------------------

struct T_DESCRIPCION_FRAME_ANIMACION numeros_0000 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/numeros/numero0000.png"          // char *ruta ;
} ;




struct T_DESCRIPCION_FRAME_ANIMACION numeros_0001 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/numeros/numero0001.png"          // char *ruta ;
} ;




struct T_DESCRIPCION_FRAME_ANIMACION numeros_0002 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/numeros/numero0002.png"          // char *ruta ;
} ;




struct T_DESCRIPCION_FRAME_ANIMACION numeros_0003 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/numeros/numero0003.png"          // char *ruta ;
} ;




struct T_DESCRIPCION_FRAME_ANIMACION numeros_0004 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/numeros/numero0004.png"          // char *ruta ;
} ;




struct T_DESCRIPCION_FRAME_ANIMACION numeros_0005 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/numeros/numero0005.png"          // char *ruta ;
} ;




struct T_DESCRIPCION_FRAME_ANIMACION numeros_0006 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/numeros/numero0006.png"          // char *ruta ;
} ;




struct T_DESCRIPCION_FRAME_ANIMACION numeros_0007 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/numeros/numero0007.png"          // char *ruta ;
} ;




struct T_DESCRIPCION_FRAME_ANIMACION numeros_0008 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/numeros/numero0008.png"          // char *ruta ;
} ;




struct T_DESCRIPCION_FRAME_ANIMACION numeros_0009 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/numeros/numero0009.png"          // char *ruta ;
} ;




struct T_DESCRIPCION_FRAME_ANIMACION numeros_0010 = {

  10,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/numeros/numero0010.png"          // char *ruta ;
} ;




struct T_DESCRIPCION_ANIMACION animacion_numeros = {

  // int modo_loop ;

  SPRITES_LOOP_OFF,

  //! Número de frames de la animación

  11,

  // struct T_DESCRIPCION_FRAME_ANIMACION *descripcion_frames ;

  {
    &numeros_0000,
    &numeros_0001,
    &numeros_0002,
    &numeros_0003,
    &numeros_0004,
    &numeros_0005,
    &numeros_0006,
    &numeros_0007,
    &numeros_0008,
    &numeros_0009,
    &numeros_0010
  }
} ;





// ------------------------------------------------------------------------------------------------
//                                         PlayDude
// ------------------------------------------------------------------------------------------------

struct T_DESCRIPCION_FRAME_ANIMACION playdude_0000 = {

  3,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/playdude/sprite_playdude0000.png"          // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION playdude_0001 = {

  3,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/playdude/sprite_playdude0001.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION playdude_0002 = {

  3,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/playdude/sprite_playdude0002.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION playdude_0003 = {

  3,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/playdude/sprite_playdude0003.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION playdude_0004 = {

  3,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/playdude/sprite_playdude0004.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION playdude_0005 = {

  3,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/playdude/sprite_playdude0005.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION playdude_0006 = {

  3,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/playdude/sprite_playdude0006.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION playdude_0007 = {

  3,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/playdude/sprite_playdude0007.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION playdude_0008 = {

  3,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/playdude/sprite_playdude0008.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION playdude_0009 = {

  3,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/playdude/sprite_playdude0009.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION playdude_0010 = {

  3,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/playdude/sprite_playdude0010.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION playdude_0011 = {

  3,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/playdude/sprite_playdude0011.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION playdude_0012 = {

  3,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/playdude/sprite_playdude0012.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION playdude_0013 = {

  3,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/playdude/sprite_playdude0013.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION playdude_0014 = {

  3,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/playdude/sprite_playdude0014.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION playdude_0015 = {

  3,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/playdude/sprite_playdude0015.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION playdude_0016 = {

  3,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/playdude/sprite_playdude0016.png"           // char *ruta ;
} ;


struct T_DESCRIPCION_FRAME_ANIMACION playdude_0017 = {

  3,                                    // int duracion ;

  0,                                     // int hx ;
  0,                                     // int hy ;

  "data/playdude/sprite_playdude0017.png"           // char *ruta ;
} ;





struct T_DESCRIPCION_ANIMACION animacion_playdude = {

  // int modo_loop ;

  SPRITES_LOOP_ON,

  //! Número de frames de la animación

  18,

  // struct T_DESCRIPCION_FRAME_ANIMACION *descripcion_frames ;

  {
    &playdude_0000,
    &playdude_0001,
    &playdude_0002,
    &playdude_0003,
    &playdude_0004,
    &playdude_0005,
    &playdude_0006,
    &playdude_0007,
    &playdude_0008,
    &playdude_0009,
    &playdude_0010,
    &playdude_0011,
    &playdude_0012,
    &playdude_0013,
    &playdude_0014,
    &playdude_0015,
    &playdude_0016,
    &playdude_0017
  }
} ;
