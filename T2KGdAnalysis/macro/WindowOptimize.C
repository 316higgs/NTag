#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void WindowOptimizeNoiseRate() {
  TFile* fin = new TFile("../output/test.root");

  TGraphErrors* g_win1 = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;1");
  TGraphErrors* g_win2 = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;2");
  TGraphErrors* g_win3 = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;3");
  TGraphErrors* g_win4 = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;4");
  TGraphErrors* g_win5 = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;5");
  TGraphErrors* g_win6 = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;6");

  gROOT -> SetStyle("Plain");

  TCanvas* c = new TCanvas("c","c",800,800);
  //c -> SetLogy();
  //c -> Update();
  c -> SetGrid();
  TH1F* frame = gPad->DrawFrame(0.3, 0., 1., 0.04);
  frame -> SetXTitle("TMVAOutput");
  //frame -> SetYTitle("Mis-tagged Noise Rate");
  frame -> SetTitleOffset(1.1, "Y");
  g_win1 -> Draw("PL");
  g_win2 -> Draw("SAMEPL");
  g_win3 -> Draw("SAMEPL");
  g_win4 -> Draw("SAMEPL");
  g_win5 -> Draw("SAMEPL");
  g_win6 -> Draw("SAMEPL");
  c -> SaveAs("../figure/WindowOptimize.NoiseRate.pdf");

}