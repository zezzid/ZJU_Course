#include "__cf_untitled.h"
#include "rtwtypes.h"
#define EXTERN_C
#include <stdio.h>
#include <string.h>
#if defined(_MSC_VER) && (_MSC_VER < 1600)
typedef unsigned short uint16_t ;
#elif defined(__LCC__)
typedef unsigned short uint16_t ;
#else
#include <stdint.h>
#endif
EXTERN_C uint16_t getCommServicePort ( ) ; static char serverInfoFileName [
1024 ] ; static bool writePortNumToServerInfoFile = false ; static unsigned
short port = 17726U ;
#ifdef __cplusplus
#define MMI_EXTERN extern "C"
#else
#define MMI_EXTERN extern
#endif
#include "rtw_modelmap.h"
MMI_EXTERN rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr ; MMI_EXTERN
boolean_T gblExtModeEnabled ;
#include "ParamTuningTgtAppSvc/ParamTuningTgtAppSvcCIntrf.h"
EXTERN_C void TgtConnBackgroundTask ( ) { } EXTERN_C const char * TgtConnInit
( int_T argc , char_T * argv [ ] ) { const char * result = NULL ; if ( !
gblExtModeEnabled ) return ( result ) ; { int_T tvar ; for ( tvar = 1 ; tvar
< argc ; tvar ++ ) { if ( argv [ tvar ] == NULL ) continue ; if ( strcmp (
argv [ tvar ] , "-tgtconn_port" ) == 0 ) { char tmpstr [ 2 ] ; const char *
portStr = ( char * ) argv [ tvar + 1 ] ; int itemsConverted = sscanf (
portStr , "%hd%1s" , & port , tmpstr ) ; if ( itemsConverted != 1 || ( ( port
!= 0 && port < 255 ) || port > 65535 ) ) { result =
"Illegal port value for target connectivity comm service\n" ; return ( result
) ; } argv [ tvar ++ ] = NULL ; argv [ tvar ] = NULL ; continue ; } if (
strcmp ( argv [ tvar ] , "-tgtconn_server_info_file" ) == 0 ) {
writePortNumToServerInfoFile = true ; sprintf ( serverInfoFileName , "%s" ,
argv [ tvar + 1 ] ) ; argv [ tvar ++ ] = NULL ; argv [ tvar ] = NULL ;
continue ; } } port = getCommServicePort ( ) ; if (
writePortNumToServerInfoFile ) { FILE * fh ; fh = fopen ( serverInfoFileName
, "w" ) ; if ( fh == NULL ) { result =
"Unable to create target connectivity server info file\n" ; return ( result )
; } ( void ) fprintf ( fh , "Server Port Number: %d\n" , ( unsigned int )
port ) ; fclose ( fh ) ; } } if ( startParamTuningTgtAppSvc ( ) ) { result =
"Could not start ParamTuning app service" ; return ( result ) ; } return (
result ) ; } EXTERN_C void TgtConnTerm ( ) { terminateParamTuningTgtAppSvc (
) ; } EXTERN_C void TgtConnPreStep ( int_T tid ) { UNUSED_PARAMETER ( tid ) ;
tunePendingParameterChanges ( rt_modelMapInfoPtr ) ; } EXTERN_C void
TgtConnPostStep ( int_T tid ) { UNUSED_PARAMETER ( tid ) ; }
