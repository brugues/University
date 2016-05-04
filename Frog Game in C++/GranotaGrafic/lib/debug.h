#ifndef __DEBUG_INCLUDED_
#define __DEBUG_INCLUDED_

#ifdef _WIN32
  #include <crtdbg.h>
#endif

// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------

#ifdef _WIN32
  #define ASSERT      _ASSERT
#endif

//! Imprime un mensaje de texto en la consola de debug
#define LOG(...)          { log_msg(__VA_ARGS__) ; }


// ------------------------------------------------------------------------------------------------
//
// ------------------------------------------------------------------------------------------------

//! Función auxiliar para facilitar el uso de macros con parámetros variables
void log_msg(const char *format_string, ...) ;

#endif
