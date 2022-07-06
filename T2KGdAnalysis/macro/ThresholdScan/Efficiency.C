#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void Efficiency() {
  TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.etagOFF.root");

  TGraphErrors* g_NNEff    = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;13");
  TGraphErrors* g_NNHEff   = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;14");
  TGraphErrors* g_NNGdEff  = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;15");

  TGraphErrors* g_OverallEff    = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;16");
  TGraphErrors* g_OverallHEff   = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;17");
  TGraphErrors* g_OverallGdEff  = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;18");

  gROOT -> SetStyle("Plain");

  TCanvas* c = new TCanvas("c","c",800,800);
  c -> SetGrid();
  TH1F* frame = gPad->DrawFrame(0., 0., 1., 1.);
  frame -> SetXTitle("TMVAOutput");
  frame -> SetYTitle("Overall Tagging Efficiency");
  frame -> SetTitleOffset(1.2, "Y");
  g_OverallEff   -> Draw("PL");
  g_OverallHEff  -> Draw("SAMEPL");
  g_OverallGdEff -> Draw("SAMEPL");

  TCanvas* cNN = new TCanvas("cNN","cNN",800,800);
  cNN -> SetGrid();
  TH1F* frameNN = gPad->DrawFrame(0., 0., 1., 1.);
  frameNN -> SetXTitle("TMVAOutput");
  frameNN -> SetYTitle("NN Classification Efficiency");
  frameNN -> SetTitleOffset(1.2, "Y");
  g_NNEff   -> Draw("PL");
  g_NNHEff  -> Draw("SAMEPL");
  g_NNGdEff -> Draw("SAMEPL");
}