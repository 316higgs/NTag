#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void Purity() {
  TFile* fin   = new TFile("../../output/test.root");

  TGraphErrors* g_Purity    = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;19");
  TGraphErrors* g_NoiseRate = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;1");

  gROOT -> SetStyle("Plain");
  TCanvas* c = new TCanvas("c","c",800,800);
  c -> SetGrid();
  TH1F* frame = gPad->DrawFrame(0., 0., 1., 1.);
  frame -> SetXTitle("TMVAOutput");
  //frame -> SetYTitle("Mis-tagged Noise Rate");
  frame -> SetTitleOffset(1.1, "Y");
  g_NoiseRate -> Draw("PL");
  g_Purity    -> Draw("SAMEPL");
  //c -> SaveAs("../figure/WindowOptimize.NoiseRate.pdf");
}