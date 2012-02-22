
%apply int { uint8_t };
%apply int { uint32_t };
%apply int { int32_t };
%apply int { int8_t };

#ifdef SWIGCSHARP  
%module Xpress 
#else
%module xpress
#endif
%{
  /* Includes the header in the wrapper code */
#include <wiring_export.h>
#include <pin_constants.h>

%}
          
/* Parse the header file to generate wrappers */
%include <wiring_export.h>
%include <pin_constants.h>
 
