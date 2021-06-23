//geotnk.hh
//   2006.10.09   First version  based on geotnk.h
//                                    by H.Sekiya
//
/************************************************************************
*     -----------------
*     INCLUDE 'geotnk.h'
*     -----------------
*
*     (Purpose)
*       Set basic parameters for the Super-Kamioka water tank.
*
*     (Comments)
*       Unit in cm for entire programs
*
*     (Creation Date and Author)
*       1992.01.16 ; First version by Y.Suzuki
*       1998.03.19 ; ZMED modified from 45 to 55 cm
*       2001.05.04 ; Intermedidate version for true 1kt geom by Y.Itow
*                    STEP 70.7->70cm, ID hight 862.4->854
*                    CENTINTK 54->44, still RINTK is for 70.7 spacing
* 
************************************************************************
*
*     (Modification)
*       Basic geometry parameters are now set by PARAMETER statements.
*       And variable names are changed so as to include TK at their
*       end.
*
*     (Date and Author)
*       1992.05.12 ; J. Kanzaki
*
************************************************************************
*
*     (Modification)
*       Parameters are set to the value as of OCT '93
*        New parameters for the size of the wall frame
*     
*       By Y. Suzuki (10/23/93)
*
*************************************************************************
*/
//      REAL DITKTK, HITKTK, DIINTK, HIINTK, HIWAL, TTATTK, TBATTK, 
//     &   TWATTK, RTKTK, ZPTKTK, ZMTKTK, RINTK, ZPINTK, ZMINTK, ZPWAL,
//     &   ZMWAL,ZCNTTK, RMED, ZMED

#ifdef ICHI_KILO
float CENTINTK:
//Set basic tank parameters
// DITKTK=1080.   ; Diameter of the water tank
const float DITKTK=1080.;
// HITKTK=1085.   ; Height of the water tank ( to water surface )
const float HITKTK=1080.;
// DIINTK=855.2   ; Diameter of the inner volume
const float DIINTK=860.0;
// HIINTK=862.4   ; Height of the inner volume
const float HIINTK=854.;
// HIWAL=848.4   ; Height of the barrel pmt frames
const float HIWAL=840.;
// TTATTK=55.    ; Thickness of the top anti layer
const float TTATTK=66.;
// TBATTK=52.6    ; Thickness of the bottom anti layer
const float TBATTK=64.;
// TWATTK=67.4    ; Thickness of the wall anti layer
const float TWATTK=67.4;
// CENTINTK = 54. ; Shift of center of inner volume
const float CENTINTK = 44.;      

#else

//Set basic tank parameters

// DITKTK=3930.   ; Diameter of the water tank
const float DITKTK=3930.;
// HITKTK=4140.   ; Height of the water tank ( to water surface )
const float HITKTK=4140.;
// DIINTK=3380.   ; Diameter of the inner volume
const float DIINTK=3380.;
// HIINTK=3620.   ; Height of the inner volume
const float HIINTK=3620.;
// HIWAL=3605.7   ; Height of the barrel pmt frames
const float HIWAL=3605.7;
// TTATTK=260.    ; Thickness of the top anti layer
const float TTATTK=260.;
// TBATTK=260.    ; Thickness of the bottom anti layer
const float TBATTK=260.;
// TWATTK=275.    ; Thickness of the wall anti layer
const float TWATTK=275.;

#endif

// RTKTK=DITKTK/2. ; Radius of the water tank

const float RTKTK = DITKTK/2. ;
// ZPTKTK=HITKTK/2.  ; Height of the tank from the center
const float ZPTKTK=HITKTK/2.;
// ZMTKTK=-HITKTK/2. ; -Height of the tank from the center
const float ZMTKTK=-HITKTK/2.;
// RINTK = DIINTK/2. ; Radius of the inner volume
const float RINTK=DIINTK/2.;
// ZPINTK=HIINTK/2. ; Height of the inner volume from the center
const float ZPINTK=HIINTK/2.;
// ZMINTK=-HIINTK/2. ; -Height of the inner volume from the center
const float ZMINTK=-HIINTK/2.;
// ZPWAL=HIWAL/2.   ; Height of the wall from the center
const float ZPWAL=HIWAL/2.;
// ZMWAL=-HIWAL/2.   ; -Height of the wall from the center
const float ZMWAL=-HIWAL/2.;
// ZCNTTK=HITKTK/2. ; Height of zero point (center) from the bottom ; of the tank
const float ZCNTTK=HITKTK/2.;

// Thickness of the nonsensitive regeion
#ifdef ICHI_KILO
 const float RMED  = 58.;
 const float ZMED  = 56.;
#else
 const float RMED  = 55.;
 const float ZMED  = 55.;
#endif


