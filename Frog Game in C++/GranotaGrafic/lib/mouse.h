#ifndef __MOUSE_INCLUDED_
#define __MOUSE_INCLUDED_


// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------

//! Enum de los botones del ratón

enum {

  //! Constante de control para uso interno
  BUTTON_NONE,                    // BUTTON_NONE tiene que ser >= 0 o se machacará memoria

  //! Botón principal del ratón (izquierdo en un ratón de 2 o 3 botones, o el único en un Mac)
  BUTTON_1,

  //! Botón principal del ratón (izquierdo en un ratón de 2 o 3 botones, o el único en un Mac)
  BUTTON_LEFT = BUTTON_1,

  //! Botón del medio en un ratón de 3 botones
  BUTTON_2,

  //! Botón del medio en un ratón de 3 botones
  BUTTON_MIDDLE = BUTTON_2,

  //! Botón derecho del ratón
  BUTTON_3,

  //! Botón derecho del ratón
  BUTTON_RIGHT = BUTTON_3,

  //! Constante de control para uso interno, indica a cuántos botones damos soporte
  MAX_NUM_POINTER_BUTTONS
} ;


// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------

//! \brief Estado del ratón

//! Estructura de datos donde guardamos el estado del ratón (posición, movimiento, botones, etc)

struct T_MOUSE
{
  // Posición actual del ratón en la ventana
  int x, y ;

  // Posición del ratón en la ventana en el frame anterior
  int last_x, last_y ;

  // Desplazamiento que ha hecho el ratón desde el último frame
  int offset_x, offset_y ;

  // Array de número de botones que indica si están pulsados (1) o no (0)
  int cnt[MAX_NUM_POINTER_BUTTONS] ;

  // Array de número de botones que indica si han sido pulsados este frame (1) o no (0)
  int trg[MAX_NUM_POINTER_BUTTONS] ;

  // Indican si este frame se ha pulsado la rueda del ratón. La rueda no se puede mantener
  // pulsada, así que no necesitamos distinguirlos como en el caso de los botones
  int bWheelUp, bWheelDown, bWheelLeft, bWheelRight ;
} ;


// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------

//! Esta función no está pensada para usarse directamente. Avisa de que se acaba de soltar un botón del ratón
void Mouse_ProcessButtonDown(int boton) ;

//! Esta función no está pensada para usarse directamente. Avisa de que se acaba de soltar un botón del ratón
void Mouse_ProcessButtonUp(int boton) ;

//! Esta función procesa los datos de haber movido la rueda del ratón
void Mouse_ProcessWheel(int wheelx, int wheely) ;

//! Inicializa la estructura de datos de ratón para poderla usar
void Mouse_Init() ;

//! Procesa los datos que tenemos del ratón para que luego podamos leer algo con sentido
void Mouse_Tick() ;


// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------

//! Variable que guarda el estado del ratón
extern struct T_MOUSE g_Mouse ;

#endif
