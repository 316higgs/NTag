// effwallf.cc
// effective distance from OD wall or ID wall
// 2006.10.09  based on effwallf.F by H.Sekiya
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include "geotnk.hh"
#include "effwallf.h"

using namespace std;

//cccccccccccccccccccccccccccccccccccccccccccccccccccccccc
//      real function effwallf(idod, pos, dir, poswal)
//
//     effective distance from OD wall (SUS wall) or ID wall (black sheet) 
//
//    input:
//            idod      .eq.1  from ID wall
//                      .ne.1  from OD wall
//            pos(3)    vertex position
//            dir(3)    direction
//
//     output:
//            effwallf  effective distance from poswal
//            poswal(3) extrapolated position at ID or OD wall
//
//     16-JUL-1997 first version by Y.Takeuchi 
//     09-OCT-2006 H.Sekiya
//cccccccccccccccccccccccccccccccccccccccccccccccccccccccc

double effwallf(int idod, double pos[3], double dir[3], double poswal[3])
{

  double a,b,c,t,x,y,z;
  
  if ( idod == 1 ){  //from ID wall
    // calc cross point at the barrel wall
    a = dir[0]*dir[0] + dir[1]*dir[1];
    b = dir[0]*pos[0] + dir[1]*pos[1];
    c = pos[0]*pos[0] + pos[1]*pos[1] - (RINTK)*(RINTK);
    t = (-b - sqrt(b*b - a*c)) / a;
    x = dir[0]*t + pos[0];
    y = dir[1]*t + pos[1];
    z = dir[2]*t + pos[2];

    if ( z > ZPINTK) {   //if crossed at top
      t = (ZPINTK - pos[2]) / dir[2];
      x = dir[0]*t + pos[0];
      y = dir[1]*t + pos[1];
      z = ZPINTK;
    }

    if ( z < ZMINTK) {   //if crossed at bottom
      t = (ZMINTK - pos[2]) / dir[2];
      x = dir[0]*t + pos[0];
      y = dir[1]*t + pos[1];
      z = ZMINTK;
    }

  }  else if ( idod == 0 ) {  // from OD wall  
   //calc. cross point at barrel wall
    a = dir[0]*dir[0] + dir[1]*dir[1];
    b = dir[0]*pos[0] + dir[1]*pos[1];
    c = pos[0]*pos[0] + pos[1]*pos[1] - (RTKTK)*(RTKTK);
    t = (-b - sqrt(b*b - a*c)) / a;
    x = dir[0]*t + pos[0];
    y = dir[1]*t + pos[1];
    z = dir[2]*t + pos[2];

    if (z > ZPTKTK) { // if crossed at top
      t = (ZPTKTK - pos[2]) / dir[2];
      x = dir[0]*t + pos[0];
      y = dir[1]*t + pos[1];
      z = ZPTKTK;
    }

    if (z < ZMTKTK) { // if crossed at bottom
      t = (ZMTKTK - pos[2]) / dir[2];
      x = dir[0]*t + pos[0];
      y = dir[1]*t + pos[1];
      z = ZMTKTK;
    }
  }

  // calc. eff. dist. from cross point
  double effwallf = sqrt((pos[0]-x)*(pos[0]-x)+(pos[1]-y)*(pos[1]-y)+(pos[2]-z)*(pos[2]-z));
  poswal[0] = x;
  poswal[1] = y;
  poswal[2] = z;

  return effwallf;
}
