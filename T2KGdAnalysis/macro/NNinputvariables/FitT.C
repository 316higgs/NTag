#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void FitT() {

  TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.NNtest.root");

  TH1F* h1_FitT = (TH1F*)fin->Get("NNInputVariables/h1_FitT_NHitsExcess");
  h1_FitT -> SetLineWidth(2);
  h1_FitT -> SetLineColor(kAzure-9);

  TF1* f = new TF1("f", "[0] * exp(-x/[1])", 0, 100);
  f -> SetParameter(0, 100);
  f -> SetParameter(1, 5);
  f -> SetLineWidth(2);
  f -> SetLineColor(kOrange-2);

  h1_FitT -> Fit("f", "r");

  gROOT -> SetStyle("Plain");
  gStyle -> SetOptFit(1111);
  TCanvas* c = new TCanvas("c", "c", 800, 800);
  c -> cd();
  h1_FitT -> Draw();
}