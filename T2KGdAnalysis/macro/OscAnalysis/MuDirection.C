#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void MuDirection() {
  TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.root");

  TH2F* h2_RecoMuDirectionXY = (TH2F*)fin->Get("NeutrinoOscillation/h2_RecoMuDirectionXY");
  TH2F* h2_RecoMuDirectionRZ = (TH2F*)fin->Get("NeutrinoOscillation/h2_RecoMuDirectionRZ");

  gROOT -> SetStyle("Plain");

  TCanvas* c1 = new TCanvas("c1","c1",900,900);
  c1 -> SetGrid();
  h2_RecoMuDirectionXY -> Draw();

}