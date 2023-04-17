#include "__cf_untitled.h"
#include "rt_nonfinite.h"
#include "rtGetNaN.h"
#include "rtGetInf.h"
#define NumBitsPerChar                 8U
real_T rtInf ; real_T rtMinusInf ; real_T rtNaN ; real32_T rtInfF ; real32_T
rtMinusInfF ; real32_T rtNaNF ; void rt_InitInfAndNaN ( size_t realSize ) { (
void ) ( realSize ) ; rtNaN = rtGetNaN ( ) ; rtNaNF = rtGetNaNF ( ) ; rtInf =
rtGetInf ( ) ; rtInfF = rtGetInfF ( ) ; rtMinusInf = rtGetMinusInf ( ) ;
rtMinusInfF = rtGetMinusInfF ( ) ; } boolean_T rtIsInf ( real_T value ) {
return ( boolean_T ) ( ( value == rtInf || value == rtMinusInf ) ? 1U : 0U )
; } boolean_T rtIsInfF ( real32_T value ) { return ( boolean_T ) ( ( ( value
) == rtInfF || ( value ) == rtMinusInfF ) ? 1U : 0U ) ; } boolean_T rtIsNaN (
real_T value ) { boolean_T result = ( boolean_T ) 0 ; size_t bitsPerReal =
sizeof ( real_T ) * ( NumBitsPerChar ) ; if ( bitsPerReal == 32U ) { result =
rtIsNaNF ( ( real32_T ) value ) ; } else { union { LittleEndianIEEEDouble
bitVal ; real_T fltVal ; } tmpVal ; tmpVal . fltVal = value ; result = (
boolean_T ) ( ( tmpVal . bitVal . words . wordH & 0x7FF00000 ) == 0x7FF00000
&& ( ( tmpVal . bitVal . words . wordH & 0x000FFFFF ) != 0 || ( tmpVal .
bitVal . words . wordL != 0 ) ) ) ; } return result ; } boolean_T rtIsNaNF (
real32_T value ) { IEEESingle tmp ; tmp . wordL . wordLreal = value ; return
( boolean_T ) ( ( tmp . wordL . wordLuint & 0x7F800000 ) == 0x7F800000 && (
tmp . wordL . wordLuint & 0x007FFFFF ) != 0 ) ; }
