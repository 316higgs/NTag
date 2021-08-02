///////////////////////////////////////////////////////////////////////
//
// wallsk.cc
//
// CALCULATE DISTANCE FROM THE NEAREST WALL
//
// -2006.10.10   by H.Sekiya
//            based on wallsk.F
//**********************************************************************
//     
//      FUNCTION WALLSK(POS)
//
//     CALCULATE DISTANCE FROM THE NEAREST WALL
//**********************************************************************
//
#include <iostream>
#include <fstream>
#include <iomanip>   
#include <cmath>
#include "TROOT.h"
#include "geotnk.hh"
#include "wallsk.h"

double wallsk(double pos[3]){

  double rr,r;
  double wallsk,z1,z2;

  rr = pos[0]*pos[0]+pos[1]*pos[1];
  r  = sqrt(rr);
  
  wallsk = RINTK-r;
  
  z1 = ZPINTK-pos[2];
  z2 = pos[2]-ZMINTK;

  if ( z1 < wallsk ) {
    wallsk = z1;
  }
  if ( z2 < wallsk ) {
    wallsk = z2;
  }

  return wallsk;
} 


Float_t wallsk(Float_t pos[3])
{
    double newpos[3];
    for (int i = 0; i < 3; i++) newpos[i] = pos[i];
    return (Float_t) wallsk(newpos);
}
