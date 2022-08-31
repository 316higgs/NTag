#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void Hits_x_AccNoise() {
  TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.NNtest.root");

  TH2F* h2_NHits_x_NumAccNoise = (TH2F*)fin->Get("NNInputVariables/h2_NHits_x_NumAccNoise");
  TH2F* h2_N200_x_NumAccNoise  = (TH2F*)fin->Get("NNInputVariables/h2_N200_x_NumAccNoise");

  gROOT -> SetStyle("Plain");
  gStyle->SetPalette(kCandy);
  TColor::InvertPalette();
    
  h2_NHits_x_NumAccNoise->SetContour(99);
  h2_N200_x_NumAccNoise ->SetContour(99);
  h2_NHits_x_NumAccNoise->GetYaxis()->SetTitleOffset(1.3);
  h2_N200_x_NumAccNoise ->GetYaxis()->SetTitleOffset(1.3);
    
  TCanvas* c1 = new TCanvas("c1","c1",900,900);
  c1 -> SetGrid();
  h2_NHits_x_NumAccNoise -> Draw("COLZ");

  TCanvas* c2 = new TCanvas("c2","c2",900,900);
  c2 -> SetGrid();
  h2_N200_x_NumAccNoise -> Draw("COLZ");

}
