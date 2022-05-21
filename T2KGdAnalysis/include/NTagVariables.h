#pragma once

#define CUTSTEP 21

float TMVATH[CUTSTEP];
float eTMVATH[CUTSTEP];

void InitNTagVariables() {
  for (int i=0; i<CUTSTEP; i++) {
  	TMVATH[i] = 0.;
    eTMVATH[i] = 0.;
  }
}