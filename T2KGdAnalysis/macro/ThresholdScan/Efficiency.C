#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TText.h"

void Efficiency() {
  //TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.etagOFF.root");
  //TFile* fin = new TFile("../../output/fhc/fhc.numu_x_numu.etagON.noinpmt.root");
  TFile* fin = new TFile("../../output/fhc/fhc.numubar_x_numubar.etagON.noinpmt.root");

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

  TLegend* legend = new TLegend(0.53, 0.9, 0.87, 0.94);
  legend -> SetTextSize(0.04);
  legend->AddEntry((TObject*)0,"#kern[-0.1]{noToF, -tag_e ON}","");
  legend->SetLineColor(0);
  legend->SetFillColor(0);
  legend->SetBorderSize(0);
  legend->Draw() ;

  TLegend* legend1 = new TLegend(0.7, 0.85, 0.85, 0.87);
  legend1 -> SetTextSize(0.04);
  //legend1->AddEntry((TObject*)0,"#kern[-0.5]{FHC #nu_{#mu}#rightarrow#nu_{#mu} MC}","");
  legend1->AddEntry((TObject*)0,"#kern[-0.5]{FHC #bar{#nu}_{#mu}#rightarrow#bar{#nu}_{#mu} MC}","");
  legend1->SetLineColor(0);
  legend1->SetFillColor(0);
  legend1->SetFillStyle(0);
  legend1->SetBorderSize(0);
  legend1->Draw() ;

  TCanvas* cNN = new TCanvas("cNN","cNN",800,800);
  cNN -> SetGrid();
  TH1F* frameNN = gPad->DrawFrame(0., 0., 1., 1.);
  frameNN -> SetXTitle("TMVAOutput");
  frameNN -> SetYTitle("NN Classification Efficiency");
  frameNN -> SetTitleOffset(1.2, "Y");
  g_NNEff   -> Draw("PL");
  g_NNHEff  -> Draw("SAMEPL");
  g_NNGdEff -> Draw("SAMEPL");

  legend->Draw() ;
  legend1->Draw() ;
}