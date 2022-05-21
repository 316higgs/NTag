#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void WindowOptimizeEff() {
  TFile* fin = new TFile("../output/test.root");

  TGraphErrors* g_NNEff   = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;7");
  TGraphErrors* g_HNNEff  = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;8");
  TGraphErrors* g_GdNNEff = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;9");

  TGraphErrors* g_OvEff   = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;10");
  TGraphErrors* g_HOvEff  = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;11");
  TGraphErrors* g_GdOvEff = (TGraphErrors*)fin->Get("NTagAnalysis/Graph;12");

  gROOT -> SetStyle("Plain");

  TCanvas* c1 = new TCanvas("c1","c1",800,800);
  c1 -> SetGrid();
  TH1F* frame1 = gPad->DrawFrame(190., 0., 550., 1.);
  frame1 -> SetXTitle("Time Window Maximum[#musec]");
  frame1 -> SetYTitle("NN Classification Efficiency");
  frame1 -> SetTitleOffset(1.1, "Y");
  g_NNEff   -> Draw("PL");
  g_HNNEff  -> Draw("SAMEPL");
  g_GdNNEff -> Draw("SAMEPL");
  //c1 -> SaveAs("../figure/WindowOptimize.NoiseRate.pdf");

  TCanvas* c2 = new TCanvas("c2","c2",800,800);
  c2 -> SetGrid();
  TH1F* frame2 = gPad->DrawFrame(190., 0., 550., 1.);
  frame2 -> SetXTitle("Time Window Maximum[#musec]");
  frame2 -> SetYTitle("Overall Classification Efficiency");
  frame2 -> SetTitleOffset(1.1, "Y");
  g_OvEff   -> Draw("PL");
  g_HOvEff  -> Draw("SAMEPL");
  g_GdOvEff -> Draw("SAMEPL");
  //c2 -> SaveAs("../figure/WindowOptimize.NoiseRate.pdf");

}